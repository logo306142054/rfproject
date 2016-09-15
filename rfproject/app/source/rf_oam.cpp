#include "../prih/rf_oam.h"

//�����Ҫ���յ�����
void CRFOam::AddCmd(CRFCmdDispatcher &cmdDispacher)
{
}

//����ַ�
bool CRFOam::Dispatch(WORD wCmdID, CInStream &paraInStream, COutStream &resultOutStream)
{
    VOS_Output("mute::dispach id=[0x%x], paralen=%d\n", wCmdID, paraInStream.GetLen());
    CRFCmdUtil::SendCmd(m_byPortID, wCmdID, 0, resultOutStream);
    return true;
}

//��Ӧ�������
bool CRFOam::Response(WORD wCmdID, WORD wError, CInStream &instream)
{
    VOS_Output("mute::response id=[0x%x], wError=%d, paralen=%d\n", wCmdID, wError, instream.GetLen());
    if (wCmdID == 0x4f05)
    {
        return false;
    }
    return true;
}

//ִ��Action����(ȡ���۲���ģʽ�е�update())
void CRFOam::Receive(CRFEvent &event)
{

}

void CRFOam::Dump(CDumpTool &dump)
{

}

CRFOam::CRFOam(BYTE byPortID) : CRFBLL(byPortID)
{

}

CRFOam::CRFOam(BYTE byPortID, CRFCmdDispatcher &cmdDispacher, IRFActionExecutor &actionExecutor)
    : CRFBLL(byPortID, cmdDispacher, actionExecutor)
{
    SetActionExecutor(ACTIONID_OAM, actionExecutor);
    AddCmd(cmdDispacher);
}

CRFOam::~CRFOam()
{
}
