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
