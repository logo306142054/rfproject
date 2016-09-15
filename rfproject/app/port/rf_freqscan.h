#ifndef _RF_FREQSCAN_H_
#define _RF_FREQSCAN_H_

#include "../prih/rf_freqscan_base.h"

class CRFFreqscan : public CRFFreqscanBase
{
public:
    CRFFreqscan(BYTE byPortID);
    CRFFreqscan(BYTE byPortID, CRFCmdDispatcher &, IRFActionExecutor &);
    virtual ~CRFFreqscan();
};

#endif
