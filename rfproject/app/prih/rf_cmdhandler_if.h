#ifndef _RF_CMD_HANDLER_IF_H_
#define _RF_CMD_HANDLER_IF_H_

class IRFCmdHandler
{
public:
    ~IRFCmdHandler(){}

    //添加需要接收的命令
    virtual void AddCmd(class CRFCmdDispatcher &) = 0;

    //命令分发，返回true表示不再由其他CmdHandler处理，否则该命令将继续分发给其他CmdHandler处理
    virtual bool Dispatch(WORD wCmdID, CInStream &, COutStream &) = 0;

    //响应命令处理结果，返回true表示不再由其他CmdHandler处理，否则该命令将继续分发给其他CmdHandler处理
    virtual bool Response(WORD wCmdID, WORD wError, CInStream &) = 0;

};

#endif