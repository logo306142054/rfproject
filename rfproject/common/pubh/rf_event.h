#ifndef _EVENT_H_
#define _EVENT_H_

#include "define.h"

class CRFEvent
{
public:
    //�������¼�����
    WORD m_wEventType;
    //���津���¼����¼�Դָ��
    void* m_pEventSource;
    //��Ǹ��¼��Ƿ񱻽��ܣ�����Ϊfalse��ʾȡ���˴β���
    bool doit;
    //������Ϣ
    WORD m_wError;
    //����¼���ص�����
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