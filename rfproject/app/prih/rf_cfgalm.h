#ifndef _RF_CFGALM_H_
#define _RF_CFGALM_H_

#include "rf_business_logic_layer.h"

class CRFCfgalm :
    public CRFBLL
{
public:

    //ִ��Action����(ȡ���۲���ģʽ�е�update())
    virtual void Receive(CRFEvent &);

    //dumpģ���ڴ����
    virtual void Dump(CDumpTool &);

public:
    CRFCfgalm(BYTE byPortID);
    CRFCfgalm(BYTE byPortID, CRFCmdDispatcher &, IRFActionExecutor &);
    virtual ~CRFCfgalm();
};

#endif
