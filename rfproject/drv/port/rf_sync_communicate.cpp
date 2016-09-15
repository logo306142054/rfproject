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

//�������ͬ��ͨ�ŵ��豸���ڴ�ֱ�ӽ���Ӧ���������resultOutStream����
WORD CRFCommunicate::SendCmd(BYTE, ST_CMDPACKAGE &stCmdPackage, COutStream &resultOutStream)
{
    // TODO������TR�ӿڴ�������
    WORD wTRCmdID = SwitchToTRCmd(stCmdPackage.m_wCmdID);
    resultOutStream << (WORD)CMDERR_SUCCESS << (BYTE)1;

    //���¼��ϱ����ϲ㴦��
    CCmdPackage pack;
    pack.SetCodeID(stCmdPackage.m_wCmdID);
    CRFEvent event(NOTIFY_TR_CMD_RESPONSE, CMDERR_SUCCESS, &pack);
    TrigerEvent(event);

    return CMDERR_SUCCESS;
}

//����ͨ��״̬
void CRFCommunicate::SetCommunState(BYTE , E_COMMUN_STATE eCommunState)
{
    m_eCommunState = eCommunState;
}

//����ϲ��������������Ӧ������������ü�����(controllmediator)����
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
    //m_pRFCommunicate���ⲿ��controlmediator�������ͷ��ڴ�
    CRFCommunicate::m_pRFCommunicate = NULL;
}
