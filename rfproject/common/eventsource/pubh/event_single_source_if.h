#pragma once

class IEventListener;

class IEventSingleSource
{
public:

    //���õ�һ�¼�������
    virtual void SetSingleListener(IEventListener *pListener) = 0;

    virtual ~IEventSingleSource() {}
};