#ifndef _RF_COMMUNICATION_IF_H_
#define _RF_COMMUNICATION_IF_H_

#include "rf_eventlistener_if.h"

class IRFCommunicate
{
public:
    //发送命令
    virtual WORD SendCmd(BYTE byPortID, ST_CMDPACKAGE &, COutStream &) = 0;

    //设置通信状态
    virtual void SetCommunState(BYTE byPortID, E_COMMUN_STATE ) = 0;

    //清除指定byPortID的命令队列
    virtual void ClearAllCmds(BYTE byPortID) = 0;

    virtual void AddListener(IRFEventListener *) = 0;

public:
    virtual ~IRFCommunicate(){};
};

extern IRFCommunicate* GetCommunicateInstance();

#endif
