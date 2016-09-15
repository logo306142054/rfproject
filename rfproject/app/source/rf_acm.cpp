#include "../prih/rf_acm.h"

//�����Ҫ���յ�����
void CRFAcm::AddCmd(CRFCmdDispatcher &cmdDispacher)
{
}

//����ַ�
bool CRFAcm::Dispatch(WORD wCmdID, CInStream &paraInStream, COutStream &resultOutStream)
{
    VOS_Output("CRFAcm::dispach id=[0x%x], paralen=%d\n", wCmdID, paraInStream.GetLen());
    CmdPacketInfo cmdPacketInfo;
    cmdPacketInfo.wCMDID = wCmdID;
    CRFCmdUtil::SendCmd(m_byPortID, wCmdID, reinterpret_cast<DWORD>(&cmdPacketInfo), resultOutStream);
    return true;
}

//��Ӧ�������
bool CRFAcm::Response(WORD wCmdID, WORD wError, CInStream &instream)
{
    VOS_Output("CRFAcm::response id=[0x%x], wError=%d, paralen=%d\n", wCmdID, wError, instream.GetLen());
    if (wCmdID == 0x4f05)
    {
        return false;
    }
    return true;
}

//ִ��Action����(ȡ���۲���ģʽ�е�update())
void CRFAcm::Receive(CRFEvent &event)
{

}

void CRFAcm::Dump(CDumpTool &dump)
{

}

CRFAcm::CRFAcm(BYTE byPortID) : CRFBLL(byPortID)
{

}

CRFAcm::CRFAcm(BYTE byPortID, CRFCmdDispatcher &cmdDispacher, IRFActionExecutor &actionExecutor)
    : CRFBLL(byPortID, cmdDispacher, actionExecutor)
{
    SetActionExecutor(ACTIONID_ACM, actionExecutor);
    AddCmd(cmdDispacher);
}

CRFAcm::~CRFAcm()
{
}
