#ifndef _ILISTENER_CONTAINER_IF_H_
#define _ILISTENER_CONTAINER_IF_H_

#include "eventlistener_if.h"

class IEventSource
{
public:
    //����¼�����������ָ����Ҫ�������¼�ID
    virtual void AddListener(WORD wEventType, class IEventListener *pListener) = 0;

    //����¼�������
    virtual void AddListener(class IEventListener *pListener) = 0;

    //�����¼������¼�����������
    virtual void TrigerEvent(CMessage &message) = 0;
};

#endif