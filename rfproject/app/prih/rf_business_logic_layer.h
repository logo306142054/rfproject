#ifndef _RF_BLL_H_
#define _RF_BLL_H_

#include "rf_business_logic_layer_if.h"
#include "rf_cmdutil.h"

class CRFBLL : public IRFBLL
{
public:
    //子类依需要覆盖实现，添加需要接收的命令
    virtual void AddCmd(CRFCmdDispatcher &){}

    /*子类依需要覆盖实现
    *命令分发，返回true表示不再由其他CmdHandler处理，否则该命令将继续分发给其他CmdHandler处理
    */
    virtual bool Dispatch(WORD , CInStream &, COutStream &){ return true; }

    /*子类依需要覆盖实现
    *响应命令处理结果，返回true表示不再由其他CmdHandler处理，否则该命令将继续分发给其他CmdHandler处理
    */
    virtual bool Response(WORD , WORD wError, CInStream &){ return true; }

    //子类依需要覆盖实现，dump模块内存变量
    virtual void Dump(CDumpTool &){}

    //子类依需要覆盖实现，执行Action动作(取代观察者模式中的update)
    virtual void Receive(CRFEvent &){}

    //设置Action执行器
    virtual void SetActionExecutor(EN_ACTIONID eActionID, IRFActionExecutor &actionExecutor)
    {
        m_pRFActionExecutor = &actionExecutor;
        actionExecutor.AddAction(eActionID, this);
    }

protected:
    //向指定的ACTIONID发送指令
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
    class IRFActionExecutor *m_pRFActionExecutor; //action执行器
    BYTE m_byPortID;  //端口号
};

#endif