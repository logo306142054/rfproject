#ifndef _RF_CFGALM_H_
#define _RF_CFGALM_H_

#include "rf_business_logic_layer.h"

class CRFCfgalm :
    public CRFBLL
{
public:

    //执行Action动作(取代观察者模式中的update())
    virtual void Receive(CRFEvent &);

    //dump模块内存变量
    virtual void Dump(CDumpTool &);

public:
    CRFCfgalm(BYTE byPortID);
    CRFCfgalm(BYTE byPortID, CRFCmdDispatcher &, IRFActionExecutor &);
    virtual ~CRFCfgalm();
};

#endif
