#ifndef _RF_DPD_H_
#define _RF_DPD_H_

#include "wlan_business_logic_layer.h"

class CRFDpd : public CApBLL
{
public:

    //命令分发
    virtual bool Dispatch(WORD wCmdID, CRtnInStream &, CRtnOutStream &);

    //响应命令处理结果
    virtual bool Response(WORD wCmdID, WORD wError, CRtnInStream &);

    //执行Action动作(取代观察者模式中的update())
    virtual void Execute(CMessage *);

    //dump模块内存变量
    virtual void Dump(CDumpTool &);

public:
    CRFDpd(BYTE byPortID);
    CRFDpd(BYTE byPortID, CRFCmdDispatcher &, IActionExecutor &);
    virtual ~CRFDpd();
};

#endif
