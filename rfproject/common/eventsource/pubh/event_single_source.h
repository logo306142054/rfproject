#pragma once

#include "event_source_if.h"
#include "event_single_source_if.h"

class CEventSingleSource : public IEventSource, public IEventSingleSource
{
public:
    // 通过 IEventSingleSource 继承
    virtual void SetSingleListener(IEventListener * pListener);

    // 通过 IEventSource 继承
    virtual void AddListener(WORD wEventType, IEventListener * pListener);
    virtual void RemoveListener(IEventListener * pListener);
    virtual void TrigerEvent(CMessage & message);
    virtual void TrigerEvent(WORD wEventType, WORD wError);

 

public:
    virtual ~CEventSingleSource();

private:
    IEventListener * m_pSingleListener;
};