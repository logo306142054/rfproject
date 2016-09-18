#ifndef _ACTIVEE_OBJECT_ENGINE_H_
#define _ACTIVEE_OBJECT_ENGINE_H_

#include <list>
#include "runnable_if.h"

class ICommand;

class ActiveObjectEngine : public IRunnable {

public:
    virtual void Run();

    void AddCommand(ICommand & cmd);

    void Continue();

    void Pause();

private:
    bool isContinue();

public:
    ActiveObjectEngine();
    virtual ~ActiveObjectEngine();

private:
    std::list<ICommand*> m_cmds;
    bool m_pause;
};

#endif