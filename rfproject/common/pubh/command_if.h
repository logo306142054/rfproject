#ifndef _COMMAND_IF_H_
#define _COMMAND_IF_H_

class CMessage;

class ICommand
{
public:
    //Ω” ’execute÷∏¡Ó
    virtual void Execute(CMessage *pMessage) = 0;

    virtual ~ICommand(){}
};

#endif