#ifndef _LISTENER_CONTAINER_H_
#define _LISTENER_CONTAINER_H_

#include "event_source_if.h"

class CEventSource : public IEventSource
{

public:
    //����¼�����������ָ����Ҫ�������¼�ID
    virtual void AddListener(WORD wEventType, IEventListener *pListener);

    // ͨ�� IEventSource �̳�
    virtual void RemoveListener(IEventListener * pListener);

    //�����¼������¼�����������
    virtual void TrigerEvent(WORD wEventType, WORD wError = 0);

    //�����¼����ɼ���������
    virtual void TrigerEvent(CMessage &message);

protected:
    //�¼������������¼�ʱ�����쳣���ɴ��������������������Ҫ����ʵ��
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
