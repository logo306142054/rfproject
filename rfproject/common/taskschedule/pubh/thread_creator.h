#pragma once

class IRunnable;
class ThreadCreator
{
public:
    virtual void Start() = 0;
    virtual void Stop()
    {
        m_stop = true;
    }

protected:
    virtual inline bool IsContinue()
    {
        return !m_stop;
    }

public:
    ThreadCreator(IRunnable * pRunnable, char *taskName)
    {
        m_stop = true;
        m_dwTaskId = 0;
        m_pRunnable = pRunnable;
        m_taskName = taskName;
    }

    virtual ~ThreadCreator() {}

protected:
    bool m_stop;
    IRunnable * m_pRunnable;
    unsigned long m_dwTaskId;
    char * m_taskName;
};

extern ThreadCreator * CreateNewThread(IRunnable * pRunnable, char *taskName);