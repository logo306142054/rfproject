#ifndef _LISTENER_CONTAINER_H_
#define _LISTENER_CONTAINER_H_

#include "rf_eventsource_if.h"


class CRFEventSource : public IRFEventSource
{
public:
    //添加事件监听器
    virtual void AddListener(class IRFEventListener *pListener)
    {

    }

    //添加事件监听器，并指定需要监听的事件ID
    virtual void AddListener(WORD wEventType, class IRFEventListener *pListener)
    {
        if (NULL != pListener)
        {
            LisPoint point;
            point.wEventType = wEventType;
            point.pListener = pListener;
            listeners.push_back(point);
        }
    }

protected:
    //触发事件，由事件监听器处理
    virtual void TrigerEvent(WORD wEventType, WORD wError = 0)
    {
        CRFEvent event;
        event.m_wEventType = wEventType;
        event.m_wError = wError;
        TrigerEvent(event);
    }

    //触发事件，由监听器处理
    virtual void TrigerEvent(CRFEvent &event)
    {
        std::list<LisPoint>::iterator pos = listeners.begin();
        while (pos != listeners.end())
        {
            LisPoint point = (LisPoint)(*pos);
            if ((point.wEventType == event.m_wEventType) && (NULL != point.pListener))
            {
                if (CMDERR_SUCCESS != (point.pListener)->EventHandle(event))
                {
                    ExceptionHandle(point.pListener, event);
                }
            }
            pos++;
        }
    }

    //事件监听器处理事件时发生异常，由此做后续处理
    virtual void ExceptionHandle(const class IRFEventListener *, CRFEvent &)
    {

    }

public:
    virtual ~CRFEventSource()
    {
        listeners.clear();
    }

private:

    typedef struct _LISTENER_POINT
    {
        WORD wEventType;
        IRFEventListener *pListener;
    }LisPoint;

    std::list<LisPoint> listeners;
};

#endif
