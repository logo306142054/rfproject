#ifndef _RF_ASYNC_PRTCL_MGR_DIFF_RTN310_H_
#define _RF_ASYNC_PRTCL_MGR_DIFF_RTN310_H_

#include "../prih/rf_prtclmgr_base.h"

class CRFAsyncPrtclMgrEx : public CRFPrtclMgrBase
{
public:
    CRFAsyncPrtclMgrEx(BYTE byPortID);
    virtual ~CRFAsyncPrtclMgrEx();
};

#endif
