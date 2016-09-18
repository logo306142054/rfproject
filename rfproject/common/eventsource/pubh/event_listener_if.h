#ifndef _ILISTENER_IF_H_
#define _ILISTENER_IF_H_

class CMessage;

class IEventListener
{
public:
    virtual WORD EventHandle(CMessage &message) = 0;

    virtual ~IEventListener() {}
};

#endif