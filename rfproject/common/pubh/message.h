#ifndef _EVENT_H_
#define _EVENT_H_

#include "define.h"

class CMessage
{
public:
    //�������¼�����
    WORD m_wMessageId;
    //���津���¼����¼�Դָ��
    void* m_pMessageSource;
    //����¼���ص�����
    void* m_pMessageData;
    //������Ϣ
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