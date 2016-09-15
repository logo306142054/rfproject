#include "rf_async_communication.h"
#include "../prih/rf_cmdswap.h"

// TODO������TR����״̬�������·�������
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

//��������
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

//����ͨ��״̬
void CRFCommunicate::SetCommunState(BYTE byPortID, E_COMMUN_STATE eCommunState)
{
    CRFPrtclMgrBase* const pPrtclMgr = GetPrtclMgrReference(byPortID);
    RETURN_IF_NULL_WITHOUT_VALUE(pPrtclMgr);

    pPrtclMgr->SetCommunState(eCommunState);
}

//���ָ��byPortID���������
void CRFCommunicate::ClearAllCmds(BYTE byPortID)
{
    CRFPrtclMgrBase* const pPrtclMgr = GetPrtclMgrReference(byPortID);
    RETURN_IF_NULL_WITHOUT_VALUE(pPrtclMgr);

    pPrtclMgr->ClearAllCmds();
}

//����ϲ���������첽ͨ���豸��������Ӧ������������ü�����(controllmediator)����
void CRFCommunicate::AddListener(IRFEventListener *pRFEventListener)
{
    CRFEventSource::AddListener(NOTIFY_TR_CMD_RESPONSE, pRFEventListener);
    CRFEventSource::AddListener(NOTIFY_TR_ONLINE, pRFEventListener);
    CRFEventSource::AddListener(NOTIFY_TR_OFFLINE, pRFEventListener);
}

//����prtclmgr�ϱ����¼�
WORD CRFCommunicate::EventHandle(CRFEvent &event)
{
    if (NOTIFY_TR_CMD_RESPONSE == event.m_wEventType)
    {
        CCmdPackage &package = *(CCmdPackage*)(event.m_pVoidData);
        WORD wCmdID = SwitchToBSCmd(package.GetCodeID());
        //TODO: ������������������Ӧ��������
        HandleSpecialCmd();
    }

    //���¼������ϱ����ϲ㴦��
    TrigerEvent(event);
    return CMDERR_SUCCESS;
}

//�жϵ�ǰ״̬���Ƿ������·�����
bool CRFCommunicate::IsAllowToSendCmd(E_COMMUN_STATE eCommunState, WORD wCmdID)
{
    //��TR��ͨ��ʧ�ܣ�TR����
    if (E_COMMUN_STATE_INTERRUPTED == eCommunState)
    {
        return false;
    }

    //flash����
    if (E_COMMUN_STATE_FLASH_TESTING == eCommunState)
    {
        // TODO: flash����������
        if (0x3f37 != wCmdID)
        {
            return false;
        }
        return true;
    }

    //TR����״̬
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

//��ȡָ��byPortID��prtclmgr������
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

    //m_pRFCommunicate���ⲿ��controlmediator�������ͷ��ڴ�
    CRFCommunicate::m_pRFCommunicate = NULL;
}
