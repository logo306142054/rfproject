#include "define.h"
#include "event_single_source.h"
#include "event_listener_if.h"
#include "message.h"

void CEventSingleSource::SetSingleListener(IEventListener * pListener)
{
    if(m_pSingleListener != pListener)
    { 
        AP_LOG_INFO(("change single listener\n"));
    }
    m_pSingleListener = pListener;
}

void CEventSingleSource::AddListener(WORD , IEventListener * pListener)
{
    SetSingleListener(pListener);
}

void CEventSingleSource::RemoveListener(IEventListener * pListener)
{
    m_pSingleListener = NULL;
}

void CEventSingleSource::TrigerEvent(CMessage & message)
{
    if (m_pSingleListener != NULL)
    {
        message.m_pMessageSource = this;
        m_pSingleListener->EventHandle(message);
    }
    else
    {
        AP_LOG_ERR(("this single listener is null"));
    }
}

void CEventSingleSource::TrigerEvent(WORD wEventType, WORD wError)
{
    TrigerEvent(CMessage(wEventType, wError));
}

CEventSingleSource::~CEventSingleSource()
{
    m_pSingleListener = NULL;
}