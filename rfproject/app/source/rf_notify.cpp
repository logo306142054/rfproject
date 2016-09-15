#include "../prih/rf_notify.h"

//执行Action(取代观察者模式中的update())
void CRFNotify::Receive(CRFEvent &)
{

}

CRFNotify::CRFNotify(BYTE byPortID, IRFActionExecutor &actionExecutor)
{
    m_byPortID = byPortID;
    actionExecutor.AddAction(ACTIONID_NOTIFY, this);
}


CRFNotify::~CRFNotify()
{
}
