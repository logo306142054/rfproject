#ifndef _COMMAND_H_
#define _COMMAND_H_

class Command {

public:
    virtual void Exectue() = 0;

    virtual ~Command(){};
};
#endif