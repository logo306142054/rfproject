#include "sleep_command.h"
#include "active_object_engine.h"


void SleepCommand::Exectue()
{
    time_t curTime;
    time(&curTime);

    if (!start)
    {
        start = true;
        m_preTime = curTime;
        m_engine.AddCommand(*this);
    }
    else if (IsContinueToSleep(curTime))
    {       
        m_engine.AddCommand(*this);
    }
    else
    {
        m_preTime = curTime;
        m_engine.AddCommand(m_cmd);
    }
}

void SleepCommand::Resume()
{
    time(&m_preTime);
}

void SleepCommand::SetSleepTime(BYTE sleepTime)
{
    m_sleepTime = sleepTime;
}

bool SleepCommand::IsContinueToSleep(time_t curTime)
{
    return difftime(curTime, m_preTime) < m_sleepTime;
}

SleepCommand::SleepCommand(BYTE sleepTime, ActiveObjectEngine & engine, Command & cmd)
    :m_sleepTime(sleepTime),
    m_engine(engine),
    m_cmd(cmd)
{
    start = false;
    Resume();
}


SleepCommand::~SleepCommand()
{
}
