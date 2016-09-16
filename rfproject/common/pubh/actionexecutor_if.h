#ifndef _ACTIOON_EXECUTOR_IF_H_
#define _ACTIOON_EXECUTOR_IF_H_

class ICommand;
class CMessage;
class IActionExecutor
{
public:
    //添加Action
    virtual void AddAction(ACTION_ID actionId, ICommand *action) = 0;

    //向指定的Action发送指令
    virtual void Post(ACTION_ID actionId, CMessage &message) = 0;

    //向所有Action发送指令
    virtual void Post(CMessage &message) = 0;

    virtual ~IActionExecutor(){}
};

#endif