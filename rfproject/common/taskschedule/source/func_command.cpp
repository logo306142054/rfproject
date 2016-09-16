#include <stdio.h>
#include "func_command.h"
#include "sleep_command.h"
#include "active_object_engine.h"


void FuncCommand::Exectue()
{
    printf("func command %c\n", m_c);
    Sleep();
}

FuncCommand::FuncCommand(char c, BYTE delayTime, BYTE sleepTime, ActiveObjectEngine& engine)
    : DelayAndRepeat(delayTime, sleepTime, engine), m_c(c)
{

}


FuncCommand::~FuncCommand()
{

}
