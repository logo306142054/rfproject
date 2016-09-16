#ifndef _ACTIVEE_OBJECT_ENGINE_H_
#define _ACTIVEE_OBJECT_ENGINE_H_
#include "command.h"
#include <list>

enum E_STATE 
{
    START,
    PAUSE,
    STOP
};

using namespace std;
class Command;

class ActiveObjectEngine {

public:
    ActiveObjectEngine();

    ~ActiveObjectEngine();

    void AddCommand(Command & cmd);

    void Run();

    void SetState(E_STATE state);

private:
    bool isStop();
    bool isPause();
private:
    list<Command*> cmds;
    E_STATE m_state;
};

#endif