#include "../prih/rf_softmgr.h"
#include "rf_cmdutil.h"

//添加需要接收的命令
void CRFSoftMgr::AddCmd(CRFCmdDispatcher &cmdDispacher)
{
}

//命令分发
bool CRFSoftMgr::Dispatch(WORD wCmdID, CInStream &paraInStream, COutStream &resultOutStream)
{
    VOS_Output("softmgr::dispach id=[0x%x], paralen=%d\n", wCmdID, paraInStream.GetLen());
    CRFCmdUtil::SendCmd(m_byPortID, wCmdID, 0, resultOutStream);
    return true;
}

//响应命令处理结果
bool CRFSoftMgr::Response(WORD wCmdID, WORD wError, CInStream &instream)
{
    VOS_Output("softmgr::response id=[0x%x], wError=%d, paralen=%d\n", wCmdID, wError, instream.GetLen());
    if (wCmdID == 0x4f05)
    {
        return false;
    }
    return true;
}

//执行Action动作(取代观察者模式中的update())
void CRFSoftMgr::Receive(CRFEvent &event)
{

}


void CRFSoftMgr::Dump(CDumpTool &dump)
{

}

CRFSoftMgr::CRFSoftMgr(BYTE byPortID) : CRFBLL(byPortID)
{

}

CRFSoftMgr::CRFSoftMgr(BYTE byPortID, CRFCmdDispatcher &cmdDispacher, IRFActionExecutor &actionExecutor)
    : CRFBLL(byPortID, cmdDispacher, actionExecutor)
{
    SetActionExecutor(ACTIONID_SOFTMGR, actionExecutor);
    AddCmd(cmdDispacher);
}

CRFSoftMgr::~CRFSoftMgr()
{
}
