#include "../prih/rf_controlmediator.h"
#include "comm_stream.h"

//��ʼ��ҵ���߼�����ģ��
void CRFControlMediator::InitBLL()
{
    InitDiffBLL();
}

//�ͷ�ҵ���߼�����ģ��
void CRFControlMediator::ReleaseBLL()
{
    ReleaseDiffBLL();

}

//����ƽ̨�·�������
void CRFControlMediator::HandleCmd(WORD wCmdID, CRtnInStream &paraInStream, CRtnOutStream &resultOutStream)
{
     m_cmdDispacher.CmdDispatch(wCmdID, paraInStream, resultOutStream);
}

//��������communication���ϱ����¼�
WORD CRFControlMediator::EventHandle(CMessage &message)
{

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
//��ʼ�����汾�����ҵ���߼�����ģ��
void CRFControlMediator::InitDiffBLL()
{
    m_pRFDpd = new CRFDpd(m_byPortID, m_cmdDispacher, m_actionExecutor);
    RETURN_NOTHING_IF_POINTER_EQUAL_NULL(m_pRFDpd);

}

//�ͷŸ��汾�����ҵ���߼�����ģ��
void CRFControlMediator::ReleaseDiffBLL()
{
    ICommand* pRFActions[] =
    {
        m_pRFDpd,
    };

    static const WORD size = COUNTOF(pRFActions);
    for (WORD i = 0; i < size; i++)
    {
        delete pRFActions[i];
    }

    m_pRFDpd = NULL;
}