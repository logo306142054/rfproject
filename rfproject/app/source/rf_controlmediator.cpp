#include "../prih/rf_controlmediator.h"
#include "rf_communication_if.h"
#include "cmdpackage.h"
#include "rf_tr_status.h"


//��ʼ��ҵ���߼�����ģ��
void CRFControlMediator::InitBLL()
{
    IRFCommunicate *pRFCommun = GetCommunicateInstance();
    if (NULL != pRFCommun)
    {
        pRFCommun->AddListener(this);
    }

    m_pRFAcm = new CRFAcm(m_byPortID, m_cmdDispacher, m_actionExecutor);
    RETURN_IF_NULL_WITHOUT_VALUE(m_pRFAcm);

    m_pRFFademargin = new CRFFademargin(m_byPortID, m_cmdDispacher, m_actionExecutor);
    RETURN_IF_NULL_WITHOUT_VALUE(m_pRFFademargin);

    m_pRFMaincfg = new CRFMainCfg(m_byPortID, m_cmdDispacher, m_actionExecutor);
    RETURN_IF_NULL_WITHOUT_VALUE(m_pRFMaincfg);

    //��������ͷ�ʽ֮��CRFAbility���Կ��Ǻϲ���CRFOam��
    m_pRFOam = new CRFOam(m_byPortID, m_cmdDispacher, m_actionExecutor);
    RETURN_IF_NULL_WITHOUT_VALUE(m_pRFOam);

    m_pRFMute = new CRFMute(m_byPortID, m_cmdDispacher, m_actionExecutor);
    RETURN_IF_NULL_WITHOUT_VALUE(m_pRFMute);

    m_pRFAlmper = new CRFAlmper(m_byPortID, m_actionExecutor);
    RETURN_IF_NULL_WITHOUT_VALUE(m_pRFAlmper);

    m_pRFNotify = new CRFNotify(m_byPortID, m_actionExecutor);
    RETURN_IF_NULL_WITHOUT_VALUE(m_pRFNotify);

    InitDiffBLL();
}

//�ͷ�ҵ���߼�����ģ��
void CRFControlMediator::ReleaseBLL()
{
    ReleaseDiffBLL();

    IRFAction* pRFActions[] =
    {
        m_pRFNotify,
        m_pRFAlmper,
        m_pRFMute,
        m_pRFOam,
        m_pRFMaincfg,
        m_pRFFademargin,
        m_pRFAcm,
    };

    const WORD size = COUNTOF(pRFActions);
    for (WORD i = 0; i < size; i++)
    {
        if (NULL != pRFActions[i])
        {
            delete pRFActions[i];
        }        
    }

    m_pRFNotify = NULL;
    m_pRFAlmper = NULL;
    m_pRFMute = NULL;
    m_pRFOam = NULL;
    m_pRFMaincfg = NULL;
    m_pRFFademargin = NULL;
    m_pRFAcm = NULL;

    if (NULL != GetCommunicateInstance())
    {
        delete GetCommunicateInstance();
    }
}

//����ƽ̨�·�������
void CRFControlMediator::HandleCmd(WORD wCmdID, CInStream &paraInStream, COutStream &resultOutStream)
{
     m_cmdDispacher.CmdDispatch(wCmdID, paraInStream, resultOutStream);
}

//��������communication���ϱ����¼�
WORD CRFControlMediator::EventHandle(CRFEvent &event)
{
    if (NOTIFY_TR_CMD_RESPONSE == event.m_wEventType)
    {
        CCmdPackage &package = *(CCmdPackage*)(event.m_pVoidData);

        WORD wError = package.GetErrorCode();
        BYTE *pbyPara = NULL;
        WORD wLen = 0;
        package.GetPara(&pbyPara, &wLen);

        m_cmdDispacher.RespDispatch(package.GetCodeID(), wError, pbyPara, wLen);

        CmdPacketInfo packetInfo;
        package.GetCmdPacketInfo(packetInfo);
        if (0 != packetInfo.GetCMDID())
        {
            printf("extpara=%x\n", packetInfo.GetCMDID());
        }
        return CMDERR_SUCCESS;
    }

    //bool bIsOnline = (NOTIFY_TR_ONLINE == event.m_wEventType) ? true : false;
    if (NOTIFY_TR_ONLINE == event.m_wEventType)
    {

    }
    else if (NOTIFY_TR_OFFLINE == event.m_wEventType)
    {

    }

    //TR��������Ϣ����������ҵ���߼�����ģ��
    m_actionExecutor.Execute(event);

    return CMDERR_SUCCESS;
}

void CRFControlMediator::Dump(CDumpTool &dump)
{

}

CRFControlMediator::CRFControlMediator(BYTE byPortID)
{
    m_byPortID = byPortID;

    InitBLL();
}


CRFControlMediator::~CRFControlMediator()
{
    ReleaseBLL();
}
