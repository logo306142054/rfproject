#include "rf_async_communication.h"
#include "../prih/rf_cmdswap.h"

// TODO：补充TR升级状态下允许下发的命令
const WORD wUpgradeCmds[] = 
{
    0x4F3A,
    0x4F3B,
    0x4F3C
};

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

//发送命令
WORD CRFCommunicate::SendCmd(BYTE byPortID, ST_CMDPACKAGE &stCmdPackage, COutStream &resultOutStream)
{
    CRFPrtclMgrBase* const pPrtclMgr = GetPrtclMgrReference(byPortID);
    RETURN_IF_NULL_WITH_VALUE(pPrtclMgr, CMDERR_ERR);

    stCmdPackage.m_wCmdID = SwitchToTRCmd(stCmdPackage.m_wCmdID);

    E_COMMUN_STATE eCommunState = pPrtclMgr->GetCommunState();
    if (!IsAllowToSendCmd(eCommunState, stCmdPackage.m_wCmdID))
    {
        resultOutStream << (WORD)CMDERR_ERR;
        return CMDERR_ERR;
    }

    return pPrtclMgr->AddCmd(stCmdPackage, resultOutStream);
}

//设置通信状态
void CRFCommunicate::SetCommunState(BYTE byPortID, E_COMMUN_STATE eCommunState)
{
    CRFPrtclMgrBase* const pPrtclMgr = GetPrtclMgrReference(byPortID);
    RETURN_IF_NULL_WITHOUT_VALUE(pPrtclMgr);

    pPrtclMgr->SetCommunState(eCommunState);
}

//清除指定byPortID的命令队列
void CRFCommunicate::ClearAllCmds(BYTE byPortID)
{
    CRFPrtclMgrBase* const pPrtclMgr = GetPrtclMgrReference(byPortID);
    RETURN_IF_NULL_WITHOUT_VALUE(pPrtclMgr);

    pPrtclMgr->ClearAllCmds();
}

//添加上层监听器，异步通信设备，命令响应结果将传递至该监听器(controllmediator)处理
void CRFCommunicate::AddListener(IRFEventListener *pRFEventListener)
{
    CRFEventSource::AddListener(NOTIFY_TR_CMD_RESPONSE, pRFEventListener);
    CRFEventSource::AddListener(NOTIFY_TR_ONLINE, pRFEventListener);
    CRFEventSource::AddListener(NOTIFY_TR_OFFLINE, pRFEventListener);
}

//接收prtclmgr上报的事件
WORD CRFCommunicate::EventHandle(CRFEvent &event)
{
    if (NOTIFY_TR_CMD_RESPONSE == event.m_wEventType)
    {
        CCmdPackage &package = *(CCmdPackage*)(event.m_pVoidData);
        WORD wCmdID = SwitchToBSCmd(package.GetCodeID());
        //TODO: 补充个别特殊命令的响应参数处理
        HandleSpecialCmd();
    }

    //将事件继续上报给上层处理
    TrigerEvent(event);
    return CMDERR_SUCCESS;
}

//判断当前状态下是否允许下发命令
bool CRFCommunicate::IsAllowToSendCmd(E_COMMUN_STATE eCommunState, WORD wCmdID)
{
    //与TR的通信失败，TR离线
    if (E_COMMUN_STATE_INTERRUPTED == eCommunState)
    {
        return false;
    }

    //flash测试
    if (E_COMMUN_STATE_FLASH_TESTING == eCommunState)
    {
        // TODO: flash测试命令字
        if (0x3f37 != wCmdID)
        {
            return false;
        }
        return true;
    }

    //TR升级状态
    if (E_COMMUN_STATE_UPGRADING == eCommunState)
    {
        static const WORD size = COUNTOF(wUpgradeCmds);
        for (WORD i = 0; i < size; i++)
        {
            if (wCmdID == wUpgradeCmds[i])
            {
                return true;
            }
        }

        return false;
    }

    return true;
}

//获取指定byPortID的prtclmgr的引用
CRFPrtclMgrBase* CRFCommunicate::GetPrtclMgrReference(BYTE byPortID)
{
    BYTE byIndex = GetIndexByPortID(byPortID);

    if (NULL == m_pPrtclMgrs[byIndex])
    {
        m_pPrtclMgrs[byIndex] = GetPrtclMgrInstance(byPortID);
        if (NULL != m_pPrtclMgrs[byIndex])
        {
            m_pPrtclMgrs[byIndex]->AddListener(this);
        }
    }

    return m_pPrtclMgrs[byIndex];
}

BYTE CRFCommunicate::GetIndexByPortID(BYTE byPortID)
{
    RTN_ASSERT(MIN_PORT <= byPortID && byPortID <= MAX_PORT);

    return byPortID - 1;
}

CRFCommunicate::CRFCommunicate()
{
    for (int i = 0; i < COUNTOF(m_pPrtclMgrs); i++)
    {
        m_pPrtclMgrs[i] = NULL;
    }
}
CRFCommunicate::~CRFCommunicate()
{
    for (int i = 0; i < COUNTOF(m_pPrtclMgrs); i++)
    {
        if (NULL != m_pPrtclMgrs[i])
        {
            delete m_pPrtclMgrs[i];
            m_pPrtclMgrs[i] = NULL;
        }
    }

    //m_pRFCommunicate由外部（controlmediator）调用释放内存
    CRFCommunicate::m_pRFCommunicate = NULL;
}
