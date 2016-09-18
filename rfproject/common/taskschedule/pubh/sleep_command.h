#pragma once
#include "command_if.h"
#include <time.h>

class ActiveObjectEngine;
class SleepCommand : public ICommand
{

public:
    virtual void Execute(CMessage *);

    void Resume();

    void SetSleepTime(BYTE sleepTime);
private:
    inline bool IsContinueToSleep(time_t curTime);
public:
    SleepCommand(BYTE delayTime, ActiveObjectEngine & engine, ICommand &  cmd);
    ~SleepCommand();

private:
    ActiveObjectEngine & m_engine;
    ICommand & m_cmd;
    BYTE m_sleepTime;
    time_t m_preTime;
    bool start;
};

