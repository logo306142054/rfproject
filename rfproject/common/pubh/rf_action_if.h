#ifndef _RF_ACTION_IF_H_
#define _RF_ACTION_IF_H_

#include "rf_event.h"

class IRFAction
{
public:
    //Ω” ’execute÷∏¡Ó
    virtual void Receive(CRFEvent &event) = 0;

    virtual ~IRFAction(){}
};

#endif