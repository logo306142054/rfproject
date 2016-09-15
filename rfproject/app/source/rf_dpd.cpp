#include "../prih/rf_dpd.h"

//�����Ҫ���յ�����
void CRFDpd::AddCmd(CRFCmdDispatcher &cmdDispacher)
{
}

//����ַ�
bool CRFDpd::Dispatch(WORD wCmdID, CInStream &paraInStream, COutStream &resultOutStream)
{
    VOS_Output("dpd::dispach id=[0x%x], paralen=%d\n", wCmdID, paraInStream.GetLen());
    CRFCmdUtil::SendCmd(m_byPortID, wCmdID, 0, resultOutStream);
    return true;
}

//��Ӧ�������
bool CRFDpd::Response(WORD wCmdID, WORD wError, CInStream &instream)
{
    VOS_Output("mute::response id=[0x%x], wError=%d, paralen=%d\n", wCmdID, wError, instream.GetLen());
    if (wCmdID == 0x4f05)
    {
        return false;
    }
    return true;
}

//ִ��Action����(ȡ���۲���ģʽ�е�update())
void CRFDpd::Receive(CRFEvent &event)
{
     VOS_Output("%RF DPD Receive eventType=%x\n", event.m_wEventType);
}

void CRFDpd::Dump(CDumpTool &dump)
{

}

CRFDpd::CRFDpd(BYTE byPortID) : CRFBLL(byPortID)
{

}

CRFDpd::CRFDpd(BYTE byPortID, CRFCmdDispatcher &cmdDispacher, IRFActionExecutor &actionExecutor)
    : CRFBLL(byPortID, cmdDispacher, actionExecutor)
{
    SetActionExecutor(ACTIONID_DPD, actionExecutor);
    AddCmd(cmdDispacher);
}

CRFDpd::~CRFDpd()
{
}
