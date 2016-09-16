#ifndef _LISTENER_CONTAINER_H_
#define _LISTENER_CONTAINER_H_

#include "eventsource_if.h"
#include "message.h"

class CEventSource : public IEventSource
{
public:
    //����¼�������
    virtual void AddListener(class IEventListener *pListener)
    {

    }

    //����¼�����������ָ����Ҫ�������¼�ID
    virtual void AddListener(WORD wEventType, class IEventListener *pListener)
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
        CMessage message;
        message.m_wMessageId = wEventType;
        message.m_wError = wError;
        TrigerEvent(message);
    }

    //�����¼����ɼ���������
    virtual void TrigerEvent(CMessage &message)
    {
        std::list<LisPoint>::iterator pos = listeners.begin();
        while (pos != listeners.end())
        {
            LisPoint point = (LisPoint)(*pos);
            if ((point.wEventType == message.m_wMessageId) && (NULL != point.pListener))
            {
                if (CMDERR_SUCCESS != (point.pListener)->EventHandle(message))
                {
                    ExceptionHandle(point.pListener, message);
                }
            }
            pos++;
        }
    }

    //�¼������������¼�ʱ�����쳣���ɴ�����������
    virtual void ExceptionHandle(const class IEventListener *, CMessage &)
    {

    }

public:
    virtual ~CEventSource()
    {
        listeners.clear();
    }

private:

    typedef struct _LISTENER_POINT
    {
        WORD wEventType;
        IEventListener *pListener;
    }LisPoint;

    std::list<LisPoint> listeners;
};

#endif
