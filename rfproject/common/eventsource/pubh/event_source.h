#ifndef _LISTENER_CONTAINER_H_
#define _LISTENER_CONTAINER_H_

#include "event_source_if.h"

class CEventSource : public IEventSource
{

public:
    //添加事件监听器，并指定需要监听的事件ID
    virtual void AddListener(WORD wEventType, IEventListener *pListener);

    // 通过 IEventSource 继承
    virtual void RemoveListener(IEventListener * pListener);

    //触发事件，由事件监听器处理
    virtual void TrigerEvent(WORD wEventType, WORD wError = 0);

    //触发事件，由监听器处理
    virtual void TrigerEvent(CMessage &message);

protected:
    //事件监听器处理事件时发生异常，由此做后续处理。子类可依需要覆盖实现
    virtual void ExceptionHandle(const IEventListener *, const CMessage &)
    {

    }

public:
    virtual ~CEventSource();

private:

    typedef struct _LISTENER_POINT
    {
        WORD wEventType;
        IEventListener *pListener;
    }LisPoint;

    std::list<LisPoint> m_listeners;
};

#endif
