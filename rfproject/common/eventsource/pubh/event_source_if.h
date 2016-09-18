#ifndef _ILISTENER_CONTAINER_IF_H_
#define _ILISTENER_CONTAINER_IF_H_

class IEventListener;
class CMessage;

class IEventSource
{
public:
    //����¼�����������ָ����Ҫ�������¼�ID
    virtual void AddListener(WORD wEventType, IEventListener *pListener) = 0;

    //�Ƴ��¼�������
    virtual void RemoveListener(IEventListener *pListener) = 0;

    //�����¼������¼�����������
    virtual void TrigerEvent(CMessage &message) = 0;

    //�����¼������¼�����������
    virtual void TrigerEvent(WORD wEventType, WORD wError = 0) = 0;

    virtual ~IEventSource() {}
};

#endif