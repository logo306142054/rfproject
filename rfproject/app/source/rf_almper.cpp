#include "../prih/rf_almper.h"


CRFAlmper::CRFAlmper(BYTE byPortID, IRFActionExecutor &actionExecutor)
{
    m_byPortID = byPortID;
    actionExecutor.AddAction(ACTIONID_ALMPER, this);
}


CRFAlmper::~CRFAlmper()
{
}
