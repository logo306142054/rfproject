#pragma once
#include "thread_creator.h"
#include <windows.h>

class WinThreadCreator : public ThreadCreator
{
public:
    WinThreadCreator(IRunnable * pRunnable, char *taskName);
    virtual void Start();
public:
    virtual ~WinThreadCreator();

private:
    HANDLE m_handle;
};
