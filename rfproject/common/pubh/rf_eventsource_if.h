#ifndef _ILISTENER_CONTAINER_IF_H_
#define _ILISTENER_CONTAINER_IF_H_

#include "rf_eventlistener_if.h"

class IRFEventSource
{
public:
    //����¼�����������ָ����Ҫ�������¼�ID
    virtual void AddListener(WORD wEventType, class IRFEventListener *pListener) = 0;

    //����¼�������
    virtual void AddListener(class IRFEventListener *pListener) = 0;

    //�����¼������¼�����������
    virtual void TrigerEvent(CMessage &message) = 0;
};

#endif