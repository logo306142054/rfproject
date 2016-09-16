#ifndef _RF_CONTROLL_MEDIATOR_H_
#define _RF_CONTROLL_MEDIATOR_H_

#include "rf_dpd.h"

#include "rf_controlmediator_if.h"
#include "rf_eventlistener_if.h"
#include "actionexecutor.h"
#include "wlan_manager_if.h"

class CRtnInStream;
class CRtnOutStream;

class CRFControlMediator : public IRFControlMediator, public IRFEventListener, public IDump
{
public:
    //处理平台下发的命令
    virtual void HandleCmd(WORD wCmdID, CRtnInStream &, CRtnOutStream &);

    //处理来自communication层上报的事件
    virtual WORD EventHandle(CMessage &event);

    virtual void Dump(CDumpTool &);
private:
    //初始化业务逻辑处理模块
    void InitBLL();

    //初始化各版本差异的业务逻辑处理模块
    void InitDiffBLL();

    //释放业务逻辑处理模块
    void ReleaseBLL();

    //释放各版本差异的业务逻辑处理模块
    void ReleaseDiffBLL();
public:
    CRFControlMediator(BYTE byPortID);
    virtual ~CRFControlMediator();

private:
  
    CRFDpd *m_pRFDpd;
    CRFCmdDispatcher m_cmdDispacher;
    CActionExecutor     m_actionExecutor;
    BYTE m_byPortID;
};

#endif

