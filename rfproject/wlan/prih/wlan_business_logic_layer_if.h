#ifndef _AP_BLL_IF_H_
#define _AP_BLL_IF_H_

#include "define.h"
#include "ap_cmd_dispatcher.h"
#include "dump_if.h"
#include "command_if.h"

class IActionExecutor;

class IWlanBLL : public ICmdHandler, public ICommand, public IDump
{
public:

    //命令分发，返回true表示不再由其他CmdHandler处理，否则该命令将继续分发给其他CmdHandler处理
    virtual bool Dispatch(WORD wCmdID, CRtnInStream &, CRtnOutStream &) = 0;

    //响应命令处理结果，返回true表示不再由其他CmdHandler处理，否则该命令将继续分发给其他CmdHandler处理
    virtual bool Response(WORD wCmdID, WORD wError, CRtnInStream &) = 0;

    //执行Action
    virtual void Execute(CMessage *) = 0;

    //设置Action执行器
    virtual void SetActionExecutor(ACTION_ID, class IActionExecutor &) = 0;

    //dump模块内存变量
    virtual void Dump(CDumpTool &) = 0;
public:
    virtual ~IWlanBLL(){};

};

#endif