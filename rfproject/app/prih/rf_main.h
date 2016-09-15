#ifndef _RF_MAIN_H_
#define _RF_MAIN_H_

#include "define.h"
#include "rf_controlmediator_if.h"

class CRFMain
{
public:
    CRFMain();
    virtual ~CRFMain();

    WORD MainBackCall();
};

#endif // _RF_MAIN_H_

