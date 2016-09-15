#include "rf_freqscan.h"

CRFFreqscan::CRFFreqscan(BYTE byPortID) : CRFFreqscanBase(byPortID)
{

}

CRFFreqscan::CRFFreqscan(BYTE byPortID, CRFCmdDispatcher &cmdDispacher, IRFActionExecutor &actionExecutor)
    : CRFFreqscanBase(byPortID, cmdDispacher, actionExecutor)
{
}

CRFFreqscan::~CRFFreqscan()
{
}
