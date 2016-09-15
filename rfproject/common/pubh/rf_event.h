#ifndef _EVENT_H_
#define _EVENT_H_

#include "define.h"

class CRFEvent
{
public:
    //触发的事件类型
    WORD m_wEventType;
    //保存触发事件的事件源指针
    void* m_pEventSource;
    //标记该事件是否被接受，设置为false表示取消此次操作
    bool doit;
    //错误信息
    WORD m_wError;
    //存放事件相关的数据
    void* m_pVoidData;

    CRFEvent()
    {
        m_wEventType = 0;
        doit = true;
        m_wError = 0;
        m_pEventSource = NULL;
        m_pVoidData = NULL;
    }

    CRFEvent(WORD wEventType, WORD wError, void* pVoidData)
    {
        m_wEventType = wEventType;
        m_wError = wError;
        m_pVoidData = pVoidData;
        m_pEventSource = NULL;
        doit = true;
    }
};

#endif