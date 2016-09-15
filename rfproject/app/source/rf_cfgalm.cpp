#include "../prih/rf_cfgalm.h"

//执行Action动作(取代观察者模式中的update())
void CRFCfgalm::Receive(CRFEvent &event)
{

}

void CRFCfgalm::Dump(CDumpTool &dump)
{

}

CRFCfgalm::CRFCfgalm(BYTE byPortID) : CRFBLL(byPortID)
{

}

CRFCfgalm::CRFCfgalm(BYTE byPortID, CRFCmdDispatcher &cmdDispacher, IRFActionExecutor &actionExecutor)
    : CRFBLL(byPortID, cmdDispacher, actionExecutor)
{
    SetActionExecutor(ACTIONID_CFGALM, actionExecutor);
}

CRFCfgalm::~CRFCfgalm()
{
}
