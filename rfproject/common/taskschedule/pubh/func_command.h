#ifndef _FUNC_COMMAND_H_
#define _FUNC_COMMAND_H_

#include "delay_and_repeat.h"

class ActiveObjectEngine;
class SleepCommand;

class FuncCommand : public DelayAndRepeat
{
public:
    virtual void Exectue();

public:
    FuncCommand(char c, BYTE delayTime, BYTE sleepTime, ActiveObjectEngine & engine);
    virtual ~FuncCommand();

private:
    char m_c;
};
#endif
