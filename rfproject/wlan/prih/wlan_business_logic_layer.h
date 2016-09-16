#ifndef _AP_BLL_H_
#define _AP_BLL_H_

#include "wlan_business_logic_layer_if.h"
#include "actionexecutor_if.h"
#include "message.h"

class CApBLL : public IWlanBLL
{
public:

    /*子类依需要覆盖实现
    *命令分发，返回true表示不再由其他CmdHandler处理，否则该命令将继续分发给其他CmdHandler处理
    */
    virtual bool Dispatch(WORD , CRtnInStream &, CRtnOutStream &){ return false; }

    /*子类依需要覆盖实现
    *响应命令处理结果，返回true表示不再由其他CmdHandler处理，否则该命令将继续分发给其他CmdHandler处理
    */
    virtual bool Response(WORD , WORD wError, CRtnInStream &){ return false; }

    //子类依需要覆盖实现，dump模块内存变量
    virtual void Dump(CDumpTool &){}

    //子类依需要覆盖实现，执行Action动作(取代观察者模式中的update)
    virtual void Execute(CMessage *){}

    //设置Action执行器
    virtual void SetActionExecutor(ACTION_ID actionId, IActionExecutor &actionExecutor)
    {
        m_pRFActionExecutor = &actionExecutor;
        actionExecutor.AddAction(actionId, this);
    }

protected:
    //向指定的ACTIONID发送指令
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
    class IActionExecutor *m_pRFActionExecutor; //action执行器
    BYTE m_byPortID;  //端口号
};

#endif