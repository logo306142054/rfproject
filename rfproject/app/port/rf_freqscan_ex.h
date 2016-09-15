#ifndef _RF_FREQSCAN_EX_H_
#define _RF_FREQSCAN_EX_H_

#include "../prih/rf_freqscan_base.h"

class CRFFreqscanEx : public CRFFreqscanBase
{
public:
    CRFFreqscanEx(BYTE byPortID);
    CRFFreqscanEx(BYTE byPortID, CRFCmdDispatcher &, IRFActionExecutor &);
    virtual ~CRFFreqscanEx();
};

#endif
