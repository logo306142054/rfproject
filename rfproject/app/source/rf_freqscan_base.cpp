#include "../prih/rf_freqscan_base.h"

//�����Ҫ���յ�����
void CRFFreqscanBase::AddCmd(CRFCmdDispatcher &cmdDispacher)
{
}

//����ַ�
bool CRFFreqscanBase::Dispatch(WORD wCmdID, CInStream &paraInStream, COutStream &resultOutStream)
{
    VOS_Output("mute::dispach id=[0x%x], paralen=%d\n", wCmdID, paraInStream.GetLen());
    CRFCmdUtil::SendCmd(m_byPortID, wCmdID, 0, resultOutStream);
    return true;
}

//��Ӧ�������
bool CRFFreqscanBase::Response(WORD wCmdID, WORD wError, CInStream &instream)
{
    VOS_Output("mute::response id=[0x%x], wError=%d, paralen=%d\n", wCmdID, wError, instream.GetLen());
    if (wCmdID == 0x4f05)
    {
        return false;
    }
    return true;
}

//ִ��Action����(ȡ���۲���ģʽ�е�update())
void CRFFreqscanBase::Receive(CRFEvent &event)
{

}

void CRFFreqscanBase::Dump(CDumpTool &dump)
{

}

CRFFreqscanBase::CRFFreqscanBase(BYTE byPortID) : CRFBLL(byPortID)
{

}

CRFFreqscanBase::CRFFreqscanBase(BYTE byPortID, CRFCmdDispatcher &cmdDispacher, IRFActionExecutor &actionExecutor)
    : CRFBLL(byPortID, cmdDispacher, actionExecutor)
{
    SetActionExecutor(ACTIONID_FREQSCAN, actionExecutor);
    AddCmd(cmdDispacher);
}

CRFFreqscanBase::~CRFFreqscanBase()
{
}
