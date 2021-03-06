#ifndef _RF_CONTROLL_MEDIATOR_IF_H_
#define _RF_CONTROLL_MEDIATOR_IF_H_
#include "define.h"

class IRFControlMediator
{
public:

    virtual void HandleCmd(WORD wCmdID, CRtnInStream &, CRtnOutStream &) = 0;

    virtual ~IRFControlMediator(){};
};

#endif
