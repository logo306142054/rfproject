#include <stdio.h>
#include "define.h"
#include "scheduled_command.h"
#include "sleep_command.h"
#include "active_object_engine.h"


void ScheduledCommand::Execute(CMessage *)
{
    if (m_pCmdWantToExec != NULL)
    {
        m_pCmdWantToExec->Execute();
    }
    
    Sleep();
}

ScheduledCommand::ScheduledCommand(ICommand *pCmdWantToExec, BYTE delayTime, BYTE sleepTime, ActiveObjectEngine& engine)
    : DelayAndRepeat(delayTime, sleepTime, engine), m_pCmdWantToExec(pCmdWantToExec)
{

}


ScheduledCommand::~ScheduledCommand()
{

}
