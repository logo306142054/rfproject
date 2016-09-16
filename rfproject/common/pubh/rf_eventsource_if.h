#ifndef _ILISTENER_CONTAINER_IF_H_
#define _ILISTENER_CONTAINER_IF_H_

#include "rf_eventlistener_if.h"

class IRFEventSource
{
public:
    //添加事件监听器，并指定需要监听的事件ID
    virtual void AddListener(WORD wEventType, class IRFEventListener *pListener) = 0;

    //添加事件监听器
    virtual void AddListener(class IRFEventListener *pListener) = 0;

    //触发事件，由事件监听器处理
    virtual void TrigerEvent(CMessage &message) = 0;
};

#endif