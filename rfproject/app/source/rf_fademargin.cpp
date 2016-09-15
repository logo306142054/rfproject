#include "../prih/rf_fademargin.h"

//�����Ҫ���յ�����
void CRFFademargin::AddCmd(CRFCmdDispatcher &cmdDispacher)
{
}

//����ַ�
bool CRFFademargin::Dispatch(WORD wCmdID, CInStream &paraInStream, COutStream &resultOutStream)
{
    VOS_Output("mute::dispach id=[0x%x], paralen=%d\n", wCmdID, paraInStream.GetLen());
    CRFCmdUtil::SendCmd(m_byPortID, wCmdID, 0, resultOutStream);
    return true;
}

//��Ӧ�������
bool CRFFademargin::Response(WORD wCmdID, WORD wError, CInStream &instream)
{
    VOS_Output("mute::response id=[0x%x], wError=%d, paralen=%d\n", wCmdID, wError, instream.GetLen());
    if (wCmdID == 0x4f05)
    {
        return false;
    }
    return true;
}

//ִ��Action����(ȡ���۲���ģʽ�е�update())
void CRFFademargin::Receive(CRFEvent &event)
{

}

void CRFFademargin::Dump(CDumpTool &dump)
{

}

CRFFademargin::CRFFademargin(BYTE byPortID) : CRFBLL(byPortID)
{

}

CRFFademargin::CRFFademargin(BYTE byPortID, CRFCmdDispatcher &cmdDispacher, IRFActionExecutor &actionExecutor)
    : CRFBLL(byPortID, cmdDispacher, actionExecutor)
{
    SetActionExecutor(ACTIONID_FADING, actionExecutor);
    AddCmd(cmdDispacher);
}

CRFFademargin::~CRFFademargin()
{
}
