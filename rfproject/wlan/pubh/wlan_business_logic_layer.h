#ifndef _AP_BLL_H_
#define _AP_BLL_H_

#include "wlan_business_logic_layer_if.h"
#include "actionexecutor_if.h"
#include "message.h"

class CApBLL : public IWlanBLL
{
public:

    /*��������Ҫ����ʵ��
    *����ַ�������true��ʾ����������CmdHandler�����������������ַ�������CmdHandler����
    */
    virtual bool Dispatch(WORD , CRtnInStream &, CRtnOutStream &){ return false; }

    /*��������Ҫ����ʵ��
    *��Ӧ�������������true��ʾ����������CmdHandler�����������������ַ�������CmdHandler����
    */
    virtual bool Response(WORD , WORD wError, CRtnInStream &){ return false; }

    //��������Ҫ����ʵ�֣�dumpģ���ڴ����
    virtual void Dump(CDumpTool &){}

    //��������Ҫ����ʵ�֣�ִ��Action����(ȡ���۲���ģʽ�е�update)
    virtual void Execute(CMessage *){}

    //����Actionִ����
    virtual void SetActionExecutor(ACTION_ID actionId, IActionExecutor &actionExecutor)
    {
        m_pRFActionExecutor = &actionExecutor;
        actionExecutor.AddAction(actionId, this);
    }

protected:
    //��ָ����ACTIONID����ָ��
    void Execute(CMessage &event, ACTION_ID actionId = ACTION_ALL)
    {
        RTN_ASSERT(NULL != m_pRFActionExecutor);
        if (NULL != m_pRFActionExecutor)
        {
            m_pRFActionExecutor->Post(actionId, event);
        }
    }

public:
    CApBLL(BYTE byPortID)
    {
        m_byPortID = byPortID;
        m_pRFActionExecutor = NULL;
    }

    CApBLL(BYTE byPortID, class CRFCmdDispatcher &, class IActionExecutor &actionExecutor)
    {
        m_byPortID = byPortID;
        m_pRFActionExecutor = &actionExecutor;
    }

    virtual ~CApBLL(){}

protected:
    class IActionExecutor *m_pRFActionExecutor; //actionִ����
    BYTE m_byPortID;  //�˿ں�
};

#endif