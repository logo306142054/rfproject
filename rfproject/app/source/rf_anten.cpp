#include "../prih/rf_anten.h"

//�����Ҫ���յ�����
void CRFAnten::AddCmd(CRFCmdDispatcher &cmdDispacher)
{
}

//����ַ�
bool CRFAnten::Dispatch(WORD wCmdID, CInStream &paraInStream, COutStream &resultOutStream)
{
    VOS_Output("CRFAnten::dispach id=[0x%x], paralen=%d\n", wCmdID, paraInStream.GetLen());
    CRFCmdUtil::SendCmd(m_byPortID, wCmdID, 0, resultOutStream);
    return true;
}

//��Ӧ�������
bool CRFAnten::Response(WORD wCmdID, WORD wError, CInStream &instream)
{
    VOS_Output("CRFAnten::response id=[0x%x], wError=%d, paralen=%d\n", wCmdID, wError, instream.GetLen());
    if (wCmdID == 0x4f05)
    {
        return false;
    }
    return true;
}

//ִ��Action����(ȡ���۲���ģʽ�е�update())
void CRFAnten::Receive(CRFEvent &event)
{

}

void CRFAnten::Dump(CDumpTool &dump)
{

}

CRFAnten::CRFAnten(BYTE byPortID) : CRFBLL(byPortID)
{

}

CRFAnten::CRFAnten(BYTE byPortID, CRFCmdDispatcher &cmdDispacher, IRFActionExecutor &actionExecutor)
    : CRFBLL(byPortID, cmdDispacher, actionExecutor)
{
    SetActionExecutor(ACTIONID_ANTEN, actionExecutor);
    AddCmd(cmdDispacher);
}

CRFAnten::~CRFAnten()
{
}
