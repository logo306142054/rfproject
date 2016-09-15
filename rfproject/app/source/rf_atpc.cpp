#include "../prih/rf_atpc.h"

//�����Ҫ���յ�����
void CRFAtpc::AddCmd(CRFCmdDispatcher &cmdDispacher)
{
}

//����ַ�
bool CRFAtpc::Dispatch(WORD wCmdID, CInStream &paraInStream, COutStream &resultOutStream)
{
    VOS_Output("CRFAtpc::dispach id=[0x%x], paralen=%d\n", wCmdID, paraInStream.GetLen());
    CRFCmdUtil::SendCmd(m_byPortID, wCmdID, 0, resultOutStream);
    return true;
}

//��Ӧ�������
bool CRFAtpc::Response(WORD wCmdID, WORD wError, CInStream &instream)
{
    VOS_Output("CRFAtpc::response id=[0x%x], wError=%d, paralen=%d\n", wCmdID, wError, instream.GetLen());
    if (wCmdID == 0x4f05)
    {
        return false;
    }
    return true;
}

//ִ��Action����(ȡ���۲���ģʽ�е�update())
void CRFAtpc::Receive(CRFEvent &event)
{

}

void CRFAtpc::Dump(CDumpTool &dump)
{

}

CRFAtpc::CRFAtpc(BYTE byPortID) : CRFBLL(byPortID)
{

}

CRFAtpc::CRFAtpc(BYTE byPortID, CRFCmdDispatcher &cmdDispacher, IRFActionExecutor &actionExecutor)
    : CRFBLL(byPortID, cmdDispacher, actionExecutor)
{
    SetActionExecutor(ACTIONID_ATPC, actionExecutor);
    AddCmd(cmdDispacher);
}

CRFAtpc::~CRFAtpc()
{
}
