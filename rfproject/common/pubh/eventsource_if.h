#ifndef _ILISTENER_CONTAINER_IF_H_
#define _ILISTENER_CONTAINER_IF_H_

#include "eventlistener_if.h"

class IEventSource
{
public:
    //添加事件监听器，并指定需要监听的事件ID
    virtual void AddListener(WORD wEventType, class IEventListener *pListener) = 0;

    //添加事件监听器
    virtual void AddListener(class IEventListener *pListener) = 0;

    //触发事件，由事件监听器处理
    virtual void TrigerEvent(CMessage &message) = 0;
};

#endif