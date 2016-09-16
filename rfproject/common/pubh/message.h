#ifndef _EVENT_H_
#define _EVENT_H_

#include "define.h"

class CMessage
{
public:
    //触发的事件类型
    WORD m_wMessageId;
    //保存触发事件的事件源指针
    void* m_pMessageSource;
    //存放事件相关的数据
    void* m_pMessageData;
    //错误信息
    WORD m_wError;

    CMessage() : CMessage(0, 0, NULL, NULL)
    {
    }

    CMessage(WORD wMessageId, WORD wError, void* pMessageData = NULL, void* pMessageSource = NULL)
    {
        m_wMessageId = wMessageId;
        m_pMessageData = pMessageData;
        m_pMessageSource = NULL;
        m_wError = wError;
    }
};

#endif