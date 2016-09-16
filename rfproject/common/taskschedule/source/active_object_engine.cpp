#include "active_object_engine.h"
#include "command.h"


void ActiveObjectEngine::AddCommand(Command & cmd)
{
    cmds.push_back(&cmd);
}

void ActiveObjectEngine::Run()
{
    while (!isStop() && !cmds.empty())
    {
        if (isPause())
            continue;
        
        Command* pCmd = cmds.front();
        if (pCmd != NULL)
        { 
            pCmd->Exectue();
        }
        cmds.pop_front();
    }
}


void ActiveObjectEngine::SetState(E_STATE state)
{
    m_state = state;
}

bool ActiveObjectEngine::isStop()
{
    return m_state == STOP;
}

bool ActiveObjectEngine::isPause()
{
    return m_state == PAUSE;
}

ActiveObjectEngine::ActiveObjectEngine()
{
    m_state = PAUSE;
}

ActiveObjectEngine::~ActiveObjectEngine()
{
    cmds.clear();
}