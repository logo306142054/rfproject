#ifndef _RF_ALMPER_H_
#define _RF_ALMPER_H_

#include "rf_action_if.h"
#include "rf_actionexecutor_if.h"

class CRFAlmper : public IRFAction
{
public:
    virtual void Receive(CRFEvent &){};

public:
    CRFAlmper(BYTE byPortID, IRFActionExecutor &);
    virtual ~CRFAlmper();

private:
    BYTE m_byPortID;
};

#endif 
