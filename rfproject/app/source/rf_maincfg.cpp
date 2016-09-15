#include "../prih/rf_maincfg.h"

//添加需要接收的命令
void CRFMainCfg::AddCmd(CRFCmdDispatcher &cmdDispacher)
{
}

//命令分发
bool CRFMainCfg::Dispatch(WORD wCmdID, CInStream &paraInStream, COutStream &resultOutStream)
{
    VOS_Output("mute::dispach id=[0x%x], paralen=%d\n", wCmdID, paraInStream.GetLen());
    CRFCmdUtil::SendCmd(m_byPortID, wCmdID, 0, resultOutStream);
    return true;
}

//响应命令处理结果
bool CRFMainCfg::Response(WORD wCmdID, WORD wError, CInStream &instream)
{
    VOS_Output("mute::response id=[0x%x], wError=%d, paralen=%d\n", wCmdID, wError, instream.GetLen());
    if (wCmdID == 0x4f05)
    {
        return false;
    }
    return true;
}

//执行Action动作(取代观察者模式中的update())
void CRFMainCfg::Receive(CRFEvent &event)
{
    VOS_Output("%RF MAINCFG Receive eventType=%x\n", event.m_wEventType);
}

void CRFMainCfg::Dump(CDumpTool &dump)
{

}

CRFMainCfg::CRFMainCfg(BYTE byPortID) : CRFBLL(byPortID)
{

}

CRFMainCfg::CRFMainCfg(BYTE byPortID, CRFCmdDispatcher &cmdDispacher, IRFActionExecutor &actionExecutor)
    : CRFBLL(byPortID, cmdDispacher, actionExecutor)
{
    SetActionExecutor(ACTIONID_MAINCFG, actionExecutor);
    AddCmd(cmdDispacher);
}

CRFMainCfg::~CRFMainCfg()
{
}
