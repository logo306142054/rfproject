#ifndef _ILISTENER_CONTAINER_IF_H_
#define _ILISTENER_CONTAINER_IF_H_

class IEventListener;
class CMessage;

class IEventSource
{
public:
    //添加事件监听器，并指定需要监听的事件ID
    virtual void AddListener(WORD wEventType, IEventListener *pListener) = 0;

    //移除事件监听器
    virtual void RemoveListener(IEventListener *pListener) = 0;

    //触发事件，由事件监听器处理
    virtual void TrigerEvent(CMessage &message) = 0;

    //触发事件，由事件监听器处理
    virtual void TrigerEvent(WORD wEventType, WORD wError = 0) = 0;

    virtual ~IEventSource() {}
};

#endif