#include "../prih/rf_cfgalm.h"

//ִ��Action����(ȡ���۲���ģʽ�е�update())
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
