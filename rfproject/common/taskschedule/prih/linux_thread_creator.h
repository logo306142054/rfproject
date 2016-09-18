#pragma once
#include "thread_creator.h"


class LinuxThreadCreator : public ThreadCreator
{
public:
    LinuxThreadCreator(IRunnable * pRunnable, char *taskName);
    virtual void Start();
public:
    virtual ~LinuxThreadCreator();
};