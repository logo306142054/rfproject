#include "rf_tr_status.h"

CRFTRStatus* CRFTRStatus::m_pRFTRStatus = NULL;

CRFTRStatus* CRFTRStatus::GetInstance()
{
    if (NULL == m_pRFTRStatus)
    {
        //double lock
        m_pRFTRStatus = new CRFTRStatus();
    }

    return m_pRFTRStatus;
}

BYTE CRFTRStatus::GetTRStatus(BYTE byPortID)
{
    BYTE byIndex = GetIndexByPortID(byPortID);
    return m_stStatus[byIndex].m_byStatus;
}

void CRFTRStatus::UpdateTRStatus(BYTE byPortID, BYTE byStatus)
{
    BYTE byIndex = GetIndexByPortID(byPortID);
    m_stStatus[byIndex].m_byStatus = byStatus;
}

BYTE CRFTRStatus::GetTRResetType(BYTE byPortID)
{
    BYTE byIndex = GetIndexByPortID(byPortID);
    return m_stStatus[byIndex].m_byLastResetType;
}

void CRFTRStatus::UpdateTRResetType(BYTE byPortID, BYTE byLastResetType)
{
    BYTE byIndex = GetIndexByPortID(byPortID);
    m_stStatus[byIndex].m_byLastResetType = byLastResetType;
}

BYTE CRFTRStatus::GetIndexByPortID(BYTE byPortID)
{
    RTN_ASSERT(MIN_PORT <= byPortID && byPortID <= MAX_PORT);

    return byPortID - 1;
}