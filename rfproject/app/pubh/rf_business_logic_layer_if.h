#ifndef _RF_BLL_IF_H_
#define _RF_BLL_IF_H_

#include "rf_action_if.h"
#include "rf_actionexecutor_if.h"
#include "../prih/rf_cmd_dispatcher.h"
#include "rf_dump_if.h"

class IRFBLL : public IRFCmdHandler, public IRFAction, public IRFDump
{
public:
    //添加需要接收的命令
    virtual void AddCmd(class CRFCmdDispatcher &) = 0;

    //命令分发，返回true表示不再由其他CmdHandler处理，否则该命令将继续分发给其他CmdHandler处理
    virtual bool Dispatch(WORD wCmdID, CInStream &, COutStream &) = 0;

    //响应命令处理结果，返回true表示不再由其他CmdHandler处理，否则该命令将继续分发给其他CmdHandler处理
    virtual bool Response(WORD wCmdID, WORD wError, CInStream &) = 0;

    //执行Action(取代观察者模式中的update())
    virtual void Receive(CRFEvent &) = 0;

    //设置Action执行器
    virtual void SetActionExecutor(EN_ACTIONID, class IRFActionExecutor &) = 0;

    //dump模块内存变量
    virtual void Dump(CDumpTool &) = 0;
public:
    virtual ~IRFBLL(){};

};

#endif