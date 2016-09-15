#ifndef _RF_BLL_H_
#define _RF_BLL_H_

#include "rf_business_logic_layer_if.h"
#include "rf_cmdutil.h"

class CRFBLL : public IRFBLL
{
public:
    //��������Ҫ����ʵ�֣������Ҫ���յ�����
    virtual void AddCmd(CRFCmdDispatcher &){}

    /*��������Ҫ����ʵ��
    *����ַ�������true��ʾ����������CmdHandler�����������������ַ�������CmdHandler����
    */
    virtual bool Dispatch(WORD , CInStream &, COutStream &){ return true; }

    /*��������Ҫ����ʵ��
    *��Ӧ�������������true��ʾ����������CmdHandler�����������������ַ�������CmdHandler����
    */
    virtual bool Response(WORD , WORD wError, CInStream &){ return true; }

    //��������Ҫ����ʵ�֣�dumpģ���ڴ����
    virtual void Dump(CDumpTool &){}

    //��������Ҫ����ʵ�֣�ִ��Action����(ȡ���۲���ģʽ�е�update)
    virtual void Receive(CRFEvent &){}

    //����Actionִ����
    virtual void SetActionExecutor(EN_ACTIONID eActionID, IRFActionExecutor &actionExecutor)
    {
        m_pRFActionExecutor = &actionExecutor;
        actionExecutor.AddAction(eActionID, this);
    }

protected:
    //��ָ����ACTIONID����ָ��
    void Execute(CRFEvent &event, EN_ACTIONID eActionID = ACTIONID_ALL)
    {
        RTN_ASSERT(NULL != m_pRFActionExecutor);
        if (NULL != m_pRFActionExecutor)
        {
            m_pRFActionExecutor->Execute(eActionID, event);
        }
    }

public:
    CRFBLL(BYTE byPortID)
    {
        m_byPortID = byPortID;
        m_pRFActionExecutor = NULL;
    }

    CRFBLL(BYTE byPortID, class CRFCmdDispatcher &, class IRFActionExecutor &actionExecutor)
    {
        m_byPortID = byPortID;
        m_pRFActionExecutor = &actionExecutor;
    }

    virtual ~CRFBLL(){}

protected:
    class IRFActionExecutor *m_pRFActionExecutor; //actionִ����
    BYTE m_byPortID;  //�˿ں�
};

#endif