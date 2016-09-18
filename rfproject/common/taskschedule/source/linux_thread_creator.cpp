#include "../prih/linux_thread_creator.h"
#include "runnable_if.h"

ThreadCreator * CreateNewThread(IRunnable * pRunnable, char *taskName)
{
    return new LinuxThreadCreator(pRunnable, taskName);
}


LinuxThreadCreator::LinuxThreadCreator(IRunnable * pRunnable, char *taskName) : ThreadCreator(pRunnable, taskName)
{
    //TODO
}

void LinuxThreadCreator::Start()
{
    if (m_pRunnable != 0)
    {
        m_stop = false;
        while (IsContinue())
        {
            m_pRunnable->Run();
        }
    }
}

LinuxThreadCreator::~LinuxThreadCreator()
{
    m_stop = true;
    m_pRunnable = 0;
}
