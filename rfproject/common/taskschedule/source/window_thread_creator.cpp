#include "../prih/window_thread_creator.h"
#include "runnable_if.h"
#include <process.h>
#include <windows.h>

ThreadCreator * CreateNewThread(IRunnable * pRunnable, char *taskName)
{
    return new WinThreadCreator(pRunnable, taskName);
}

unsigned long ThreadRun(LPVOID pParam)
{
    ThreadCreator & thread = *static_cast<ThreadCreator*>(pParam);
    thread.Start();

    return 0;
}

WinThreadCreator::WinThreadCreator(IRunnable * pRunnable, char *taskName) : ThreadCreator(pRunnable, taskName)
{
    m_handle = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadRun, (void*)this, 0, &m_dwTaskId);
}

void WinThreadCreator::Start()
{
    if (m_pRunnable != NULL)
    {
        m_stop = false;
        while (IsContinue())
        {
            m_pRunnable->Run();
            Sleep(1);//释放cpu，避免cpu一直被占用
        }
    }
}

WinThreadCreator::~WinThreadCreator()
{
    m_stop = true;
    CloseHandle(m_handle);
}
