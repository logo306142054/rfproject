#ifndef _ILISTENER_IF_H_
#define _ILISTENER_IF_H_

#include "define.h"

class CMessage;

class IEventListener
{
public:
    virtual WORD EventHandle(CMessage &event) = 0;
};

#endif