#include "../prih/rf_notify.h"

//ִ��Action(ȡ���۲���ģʽ�е�update())
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
