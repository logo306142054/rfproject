#include "rf_async_prtclmgr_diff_rtn310.h"

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
