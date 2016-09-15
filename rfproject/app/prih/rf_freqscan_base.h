#ifndef _RF_FREQSCAN_BASE_H_
#define _RF_FREQSCAN_BASE_H_

#include "rf_business_logic_layer.h"

class CRFFreqscanBase :
    public CRFBLL
{
public:
    //添加需要接收的命令
    virtual void AddCmd(CRFCmdDispatcher &);

    //命令分发
    virtual bool Dispatch(WORD wCmdID, CInStream &, COutStream &);

    //响应命令处理结果
    virtual bool Response(WORD wCmdID, WORD wError, CInStream &);

    //执行Action动作(取代观察者模式中的update())
    virtual void Receive(CRFEvent &);

    //dump模块内存变量
    virtual void Dump(CDumpTool &);

public:
    CRFFreqscanBase(BYTE byPortID);
    CRFFreqscanBase(BYTE byPortID, CRFCmdDispatcher &, IRFActionExecutor &);
    virtual ~CRFFreqscanBase();
};

#endif
