#ifndef _RF_COMMUNICATION_IF_H_
#define _RF_COMMUNICATION_IF_H_

#include "rf_eventlistener_if.h"

class IRFCommunicate
{
public:
    //��������
    virtual WORD SendCmd(BYTE byPortID, ST_CMDPACKAGE &, COutStream &) = 0;

    //����ͨ��״̬
    virtual void SetCommunState(BYTE byPortID, E_COMMUN_STATE ) = 0;

    //���ָ��byPortID���������
    virtual void ClearAllCmds(BYTE byPortID) = 0;

    virtual void AddListener(IRFEventListener *) = 0;

public:
    virtual ~IRFCommunicate(){};
};

extern IRFCommunicate* GetCommunicateInstance();

#endif
