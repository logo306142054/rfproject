#include "../prih/rf_dpd.h"

//����ַ�
bool CRFDpd::Dispatch(WORD wCmdID, CRtnInStream &paraInStream, CRtnOutStream &resultOutStream)
{
    VOS_Output("dpd::dispach id=[0x%x], paralen=%d\n", wCmdID, paraInStream.GetLen());
   
    return true;
}

//��Ӧ�������
bool CRFDpd::Response(WORD wCmdID, WORD wError, CRtnInStream &instream)
{
    VOS_Output("mute::response id=[0x%x], wError=%d, paralen=%d\n", wCmdID, wError, instream.GetLen());
    if (wCmdID == 0x4f05)
    {
        return false;
    }
    return true;
}

//ִ��Action����(ȡ���۲���ģʽ�е�update())
void CRFDpd::Execute(CMessage *pMessage)
{
     VOS_Output("DPD Receive eventType=%x\n", pMessage->m_wMessageId);
}

void CRFDpd::Dump(CDumpTool &dump)
{

}

CRFDpd::CRFDpd(BYTE byPortID) : CApBLL(byPortID)
{

}

CRFDpd::CRFDpd(BYTE byPortID, CRFCmdDispatcher &cmdDispacher, IActionExecutor &actionExecutor)
    : CApBLL(byPortID, cmdDispacher, actionExecutor)
{
    SetActionExecutor(1, actionExecutor);
}

CRFDpd::~CRFDpd()
{
}
