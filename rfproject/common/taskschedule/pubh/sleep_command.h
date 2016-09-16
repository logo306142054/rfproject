#pragma once
#include "command.h"
#include <time.h>
#include "define.h"

class ActiveObjectEngine;
class SleepCommand : public Command
{

public:
    virtual void Exectue();

    void Resume();

    void SetSleepTime(BYTE sleepTime);
private:
    inline bool IsContinueToSleep(time_t curTime);
public:
    SleepCommand(BYTE delayTime, ActiveObjectEngine & engine, Command &  cmd);
    ~SleepCommand();

private:
    ActiveObjectEngine & m_engine;
    Command & m_cmd;
    BYTE m_sleepTime;
    time_t m_preTime;
    bool start;
};

