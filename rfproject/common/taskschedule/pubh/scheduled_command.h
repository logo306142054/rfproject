#pragma once

#include "delay_and_repeat.h"

class ActiveObjectEngine;
class SleepCommand;

class ScheduledCommand : public DelayAndRepeat
{
public:
    virtual void Execute(CMessage *);

public:
    ScheduledCommand(ICommand *pCmdWantToExec, BYTE delayTime, BYTE sleepTime, ActiveObjectEngine & engine);
    virtual ~ScheduledCommand();

private:
    ICommand *m_pCmdWantToExec;
};
