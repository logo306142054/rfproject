#include "rf_async_prtclmgr_diff_rtn380R1.h"

CRFPrtclMgrBase* GetPrtclMgrInstance(BYTE byPortID)
{
    return new CRFAsyncPrtclMgrEx(byPortID);
}

CRFAsyncPrtclMgrEx::CRFAsyncPrtclMgrEx(BYTE byPortID)
    : CRFPrtclMgrBase(byPortID)
{
}


CRFAsyncPrtclMgrEx::~CRFAsyncPrtclMgrEx()
{
}