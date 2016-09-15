#include "rf_sync_communicate.h"
#include "../prih/rf_cmdswap.h"
#include "cmdpackage.h"

IRFCommunicate* GetCommunicateInstance()
{
    return CRFCommunicate::GetInstance();
}

CRFCommunicate* CRFCommunicate::m_pRFCommunicate = NULL;

CRFCommunicate* CRFCommunicate::GetInstance()
{
    if (NULL == m_pRFCommunicate)
    {
        m_pRFCommunicate = new CRFCommunicate();
    }
    return m_pRFCommunicate;
}

//发送命令，同步通信的设备，在此直接将响应结果保存至resultOutStream即可
WORD CRFCommunicate::SendCmd(BYTE, ST_CMDPACKAGE &stCmdPackage, COutStream &resultOutStream)
{
    // TODO：调用TR接口处理命令
    WORD wTRCmdID = SwitchToTRCmd(stCmdPackage.m_wCmdID);
    resultOutStream << (WORD)CMDERR_SUCCESS << (BYTE)1;

    //将事件上报给上层处理
    CCmdPackage pack;
    pack.SetCodeID(stCmdPackage.m_wCmdID);
    CRFEvent event(NOTIFY_TR_CMD_RESPONSE, CMDERR_SUCCESS, &pack);
    TrigerEvent(event);

    return CMDERR_SUCCESS;
}

//设置通信状态
void CRFCommunicate::SetCommunState(BYTE , E_COMMUN_STATE eCommunState)
{
    m_eCommunState = eCommunState;
}

//添加上层监听器，命令响应结果将传递至该监听器(controllmediator)处理
void CRFCommunicate::AddListener(IRFEventListener *pRFEventListener)
{
    CRFEventSource::AddListener(NOTIFY_TR_CMD_RESPONSE, pRFEventListener);
}

CRFCommunicate::CRFCommunicate()
{
    m_eCommunState = E_COMMUN_STATE_NORMAL;
}

CRFCommunicate::~CRFCommunicate()
{
    //m_pRFCommunicate由外部（controlmediator）调用释放内存
    CRFCommunicate::m_pRFCommunicate = NULL;
}
