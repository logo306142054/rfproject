#include "active_object_engine.h"
#include "command_if.h"

using namespace std;

void ActiveObjectEngine::AddCommand(ICommand & cmd)
{
    m_cmds.push_back(&cmd);
}

void ActiveObjectEngine::Run()
{
    if (isContinue())
    {
        ICommand* pCmd = m_cmds.front();
        m_cmds.pop_front();
        if (pCmd != NULL)
        { 
            pCmd->Execute();
        }
    }
}


void ActiveObjectEngine::Pause()
{
    m_pause = true;
}

void ActiveObjectEngine::Continue()
{
    m_pause = false;
}

bool ActiveObjectEngine::isContinue()
{
    return !m_pause && !m_cmds.empty();
}

ActiveObjectEngine::ActiveObjectEngine()
{
    m_pause = false;
}

ActiveObjectEngine::~ActiveObjectEngine()
{
    m_cmds.clear();
}