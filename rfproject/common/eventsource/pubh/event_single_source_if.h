#pragma once

class IEventListener;

class IEventSingleSource
{
public:

    //设置单一事件监听器
    virtual void SetSingleListener(IEventListener *pListener) = 0;

    virtual ~IEventSingleSource() {}
};