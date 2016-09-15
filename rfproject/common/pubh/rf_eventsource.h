#ifndef _LISTENER_CONTAINER_H_
#define _LISTENER_CONTAINER_H_

#include "rf_eventsource_if.h"


class CRFEventSource : public IRFEventSource
{
public:
    //����¼�������
    virtual void AddListener(class IRFEventListener *pListener)
    {

    }

    //����¼�����������ָ����Ҫ�������¼�ID
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
    //�����¼������¼�����������
    virtual void TrigerEvent(WORD wEventType, WORD wError = 0)
    {
        CRFEvent event;
        event.m_wEventType = wEventType;
        event.m_wError = wError;
        TrigerEvent(event);
    }

    //�����¼����ɼ���������
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

    //�¼������������¼�ʱ�����쳣���ɴ�����������
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
