#include "define.h"
#include "event_source.h"
#include "event_listener_if.h"
#include "message.h"

//添加事件监听器，并指定需要监听的事件ID
void CEventSource::AddListener(WORD wEventType, IEventListener *pListener)
{
    if (NULL != pListener)
    {
        LisPoint point;
        point.wEventType = wEventType;
        point.pListener = pListener;
        m_listeners.push_back(point);
    }
}

// 通过 IEventSource 继承
void CEventSource::RemoveListener(IEventListener * pListener)
{
    std::list<LisPoint>::iterator pos = m_listeners.begin();
    while (pos != m_listeners.end())
    {
        if (((LisPoint&)(*pos)).pListener == pListener)
        {
            m_listeners.erase(pos);
            return;
        }
        pos++;
    }
}

//触发事件，由事件监听器处理
void CEventSource::TrigerEvent(WORD wEventType, WORD wError)
{
    TrigerEvent(CMessage(wEventType, wError));
}

//触发事件，由监听器处理
void CEventSource::TrigerEvent(CMessage &message)
{
    std::list<LisPoint>::iterator pos = m_listeners.begin();
    while (pos != m_listeners.end())
    {
        LisPoint &point = (LisPoint)(*pos);
        if ((point.wEventType == message.m_wMessageId) && (NULL != point.pListener))
        {
            message.m_pMessageSource = this;
            if (CMDERR_SUCCESS != (point.pListener)->EventHandle(message))
            {
                ExceptionHandle(point.pListener, message);
            }
        }
        pos++;
    }
}

CEventSource::~CEventSource()
{
    m_listeners.clear();
}