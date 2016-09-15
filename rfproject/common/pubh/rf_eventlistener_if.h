#ifndef _ILISTENER_IF_H_
#define _ILISTENER_IF_H_

#include "rf_event.h"

class IRFEventListener
{
public:
    virtual WORD EventHandle(CRFEvent &event) = 0;
};

#endif