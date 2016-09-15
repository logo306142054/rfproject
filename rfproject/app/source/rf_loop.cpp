#include "../prih/rf_loop.h"

//添加需要接收的命令
void CRFLoop::AddCmd(CRFCmdDispatcher &cmdDispacher)
{
}

//命令分发
bool CRFLoop::Dispatch(WORD wCmdID, CInStream &paraInStream, COutStream &resultOutStream)
{
    VOS_Output("loop::dispach id=[0x%x], paralen=%d\n", wCmdID, paraInStream.GetLen());
    //CRFCmdUtil::SendCmd(m_byPortID, wCmdID, resultOutStream);
    CRFCmdUtil::SendCmd(m_byPortID, wCmdID, (BYTE)(paraInStream.GetLen()), paraInStream.GetPara(), resultOutStream);
    return true;
}

//响应命令处理结果
bool CRFLoop::Response(WORD wCmdID, WORD wError, CInStream &instream)
{
    VOS_Output("loop::response id=[0x%x], wError=%d, paralen=%d\n", wCmdID, wError, instream.GetLen());
    if (wCmdID == 0x4f05)
    {
        return false;
    }
    return true;
}

//执行Action动作(取代观察者模式中的update())
void CRFLoop::Receive(CRFEvent &event)
{

}

//dump模块内存变量
void CRFLoop::Dump(CDumpTool &dump)
{

}

CRFLoop::CRFLoop(BYTE byPortID) : CRFBLL(byPortID)
{

}

CRFLoop::CRFLoop(BYTE byPortID, CRFCmdDispatcher &cmdDispacher, IRFActionExecutor &actionExecutor)
    : CRFBLL(byPortID, cmdDispacher, actionExecutor)
{
    SetActionExecutor(ACTIONID_LOOP, actionExecutor);
    AddCmd(cmdDispacher);
}

CRFLoop::~CRFLoop()
{
}
