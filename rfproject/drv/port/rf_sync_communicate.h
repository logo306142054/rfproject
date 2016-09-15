#ifndef _RF_COMMUNICATION_H_
#define _RF_COMMUNICATION_H_

#include "rf_communication_if.h"
#include "rf_eventsource.h"

class CRFCommunicate : public IRFCommunicate, public CRFEventSource
{
public:
    static CRFCommunicate* GetInstance();
public:
    //发送命令，同步通信的设备，在此直接将响应结果保存至resultStream即可
    virtual WORD SendCmd(BYTE byPortID, ST_CMDPACKAGE &, COutStream &);

    //设置通信状态
    virtual void SetCommunState(BYTE byPortID, E_COMMUN_STATE );

    //添加上层监听器
    virtual void AddListener(IRFEventListener *);

    //空实现，同步通信未使用命令队列
    virtual void ClearAllCmds(BYTE ){};

public:
    virtual ~CRFCommunicate();
private:
    //单例模式，不允许外部调用构造函数
    CRFCommunicate();

private:
    static CRFCommunicate* m_pRFCommunicate;
    E_COMMUN_STATE m_eCommunState;
};

#endif
