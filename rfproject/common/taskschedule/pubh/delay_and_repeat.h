#pragma once
#include "command_if.h"

class ActiveObjectEngine;
class SleepCommand;

class DelayAndRepeat : public ICommand
{
public:
    virtual void Execute(CMessage *pMessage = NULL) = 0;

public:
    DelayAndRepeat(BYTE delayTime, BYTE sleepTime, ActiveObjectEngine& engine);
    DelayAndRepeat(BYTE sleepTime, ActiveObjectEngine& engine);

    virtual ~DelayAndRepeat();

protected:
    /** 以构造函数中传入的sleep time开始进入sleep状态*/
    void Sleep();
    /** 以给定的sleep time开始进入sleep状态*/
    void Sleep(BYTE newSleepTime);

private:
    bool IsExecWithoutDelay();
    void AddToEngine(ICommand & cmd);
    void AddToEngineWithoutDelay();
    void AddToEngineWithDelay();

protected:
    BYTE m_sleepTime;
    BYTE m_delayTime;
    ActiveObjectEngine & m_engine;
    SleepCommand *m_pSleepOwn;
};
