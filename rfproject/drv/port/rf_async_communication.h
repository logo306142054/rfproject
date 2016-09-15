#ifndef _RF_COMMUNICATION_H_
#define _RF_COMMUNICATION_H_

#include "../prih/rf_prtclmgr_base.h"
#include "rf_eventsource.h"
#include "rf_communication_if.h"

class CRFCommunicate : public IRFCommunicate, public CRFEventSource, public IRFEventListener
{
public:
    static CRFCommunicate* GetInstance();
public:
    //发送命令
    virtual WORD SendCmd(BYTE byPortID, ST_CMDPACKAGE &, COutStream &);

    //设置通信状态
    virtual void SetCommunState(BYTE byPortID, E_COMMUN_STATE );

    //清除指定byPortID的命令队列
    virtual void ClearAllCmds(BYTE byPortID);

    //添加上层监听器
    virtual void AddListener(IRFEventListener *);

    //接收prtclmgr上报的事件
    virtual WORD EventHandle(CRFEvent &event);

protected:
    //判断当前状态下是否允许下发命令
    virtual bool IsAllowToSendCmd(E_COMMUN_STATE , WORD wCmdID);

    virtual BYTE GetIndexByPortID(BYTE byPortID);

    //对个别特殊响应结果进行预处理
    virtual void HandleSpecialCmd();

private:
    //获取指定byPortID的prtclmgr的引用
    CRFPrtclMgrBase *GetPrtclMgrReference(BYTE byPortID);

public:
    virtual ~CRFCommunicate();
private:
    //单例模式，不允许外部调用构造函数
    CRFCommunicate();
private:
    static CRFCommunicate* m_pRFCommunicate;   
    CRFPrtclMgrBase *m_pPrtclMgrs[MAX_PORT];
};

#endif
