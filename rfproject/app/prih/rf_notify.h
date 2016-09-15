#ifndef _RF_NOTIFY_H_
#define _RF_NOTIFY_H_

#include "rf_action_if.h"
#include "rf_actionexecutor_if.h"

class CRFNotify : public IRFAction
{
public:
    //Ö´ÐÐAction
    virtual void Receive(CRFEvent &);

public:
    CRFNotify(BYTE byPortID, IRFActionExecutor &);
    virtual ~CRFNotify();

private:
    BYTE m_byPortID;
};

#endif
