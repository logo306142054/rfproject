#include "rf_freqscan_ex.h"


CRFFreqscanEx::CRFFreqscanEx(BYTE byPortID) : CRFFreqscanBase(byPortID)
{

}

CRFFreqscanEx::CRFFreqscanEx(BYTE byPortID, CRFCmdDispatcher &cmdDispacher, IRFActionExecutor &actionExecutor)
    : CRFFreqscanBase(byPortID, cmdDispacher, actionExecutor)
{

}

CRFFreqscanEx::~CRFFreqscanEx()
{
}
