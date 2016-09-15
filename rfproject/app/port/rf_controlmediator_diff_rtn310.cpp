#include "../prih/rf_controlmediator.h"
#include "rf_freqscan_ex.h"

//初始化各版本差异的业务逻辑处理模块
void CRFControlMediator::InitDiffBLL()
{
    m_pRFAnten = new CRFAnten(m_byPortID, m_cmdDispacher, m_actionExecutor);
    RETURN_IF_NULL_WITHOUT_VALUE(m_pRFAnten);

    m_pRFAtpc = new CRFAtpc(m_byPortID, m_cmdDispacher, m_actionExecutor);
    RETURN_IF_NULL_WITHOUT_VALUE(m_pRFAtpc);

    m_pRFCfgalm = new CRFCfgalm(m_byPortID, m_cmdDispacher, m_actionExecutor);
    RETURN_IF_NULL_WITHOUT_VALUE(m_pRFCfgalm);

    m_pRFDpd = new CRFDpd(m_byPortID, m_cmdDispacher, m_actionExecutor);
    RETURN_IF_NULL_WITHOUT_VALUE(m_pRFDpd);

    m_pRFLoop = new CRFLoop(m_byPortID, m_cmdDispacher, m_actionExecutor);
    RETURN_IF_NULL_WITHOUT_VALUE(m_pRFLoop);

    m_pRFFreqscan = new CRFFreqscanEx(m_byPortID, m_cmdDispacher, m_actionExecutor);
    RETURN_IF_NULL_WITHOUT_VALUE(m_pRFFreqscan);

    m_pRFSoftMgr = new CRFSoftMgr(m_byPortID, m_cmdDispacher, m_actionExecutor);
    RETURN_IF_NULL_WITHOUT_VALUE(m_pRFSoftMgr);
}

//释放各版本差异的业务逻辑处理模块
void CRFControlMediator::ReleaseDiffBLL()
{
    IRFAction* pRFActions[] =
    {
        m_pRFSoftMgr,
        m_pRFFreqscan,
        m_pRFLoop,
        m_pRFDpd,
        m_pRFCfgalm,
        m_pRFAtpc,
        m_pRFAnten,
    };

    static const WORD size = COUNTOF(pRFActions);
    for (WORD i = 0; i < size; i++)
    {
        delete pRFActions[i];
    }

    m_pRFSoftMgr = NULL;
    m_pRFFreqscan = NULL;
    m_pRFLoop = NULL;
    m_pRFDpd = NULL;
    m_pRFCfgalm = NULL;
    m_pRFAtpc = NULL;
    m_pRFAnten = NULL;
}
