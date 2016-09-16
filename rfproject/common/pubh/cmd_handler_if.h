#ifndef _AP_CMD_HANDLER_IF_H_
#define _AP_CMD_HANDLER_IF_H_

class CRtnInStream;
class CRtnOutStream;

class ICmdHandler
{
public:
    virtual ~ICmdHandler(){}

    //命令分发，返回true表示不再由其他CmdHandler处理，否则该命令将继续分发给其他CmdHandler处理
    virtual bool Dispatch(WORD wCmdID, CRtnInStream &, CRtnOutStream &) = 0;

    //响应命令处理结果，返回true表示不再由其他CmdHandler处理，否则该命令将继续分发给其他CmdHandler处理
    virtual bool Response(WORD wCmdID, WORD wError, CRtnInStream &) = 0;

};

#endif