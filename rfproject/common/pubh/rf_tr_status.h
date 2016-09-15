#ifndef _RF_TR_STATUS_H_
#define _RF_TR_STATUS_H_

#include "define.h"

#define TR_SOFT_RESET 1    
#define TR_HARD_RESET 0
#define TR_ONLINE     1
#define TR_READY      0

struct ST_TRSTATUS
{
    BYTE m_byStatus;
    BYTE m_byLastResetType;

    ST_TRSTATUS()
    {
        m_byLastResetType = TR_SOFT_RESET;
        m_byStatus = TR_READY;
    }
};

class CRFTRStatus
{
public:
    static CRFTRStatus* GetInstance();

    BYTE GetTRStatus(BYTE byPortID);

    void UpdateTRStatus(BYTE byPortID, BYTE byStatus);

    BYTE GetTRResetType(BYTE byPortID);

    void UpdateTRResetType(BYTE byPortID, BYTE byLastResetType);

private:
    BYTE GetIndexByPortID(BYTE byPortID);

private:
    static CRFTRStatus* m_pRFTRStatus;

    ST_TRSTATUS m_stStatus[MAX_PORT];

public:
    ~CRFTRStatus(){}
private:
    CRFTRStatus(){}
};

#endif
