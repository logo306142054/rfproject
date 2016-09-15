#include "../prih/rf_controlmediator.h"
#include "rf_freqscan.h"

//��ʼ�����汾�����ҵ���߼�����ģ��
void CRFControlMediator::InitDiffBLL()
{
    m_pRFAnten = new CRFAnten(m_byPortID, m_cmdDispacher, m_actionExecutor);
    RETURN_IF_NULL_WITHOUT_VALUE(m_pRFAnten);

    m_pRFAtpc = new CRFAtpc(m_byPortID, m_cmdDispacher, m_actionExecutor);
    RETURN_IF_NULL_WITHOUT_VALUE(m_pRFAtpc);

    m_pRFCfgalm = new CRFCfgalm(m_byPortID, m_cmdDispacher, m_actionExecutor);
    RETURN_IF_NULL_WITHOUT_VALUE(m_pRFCfgalm);

    m_pRFFreqscan = new CRFFreqscan(m_byPortID, m_cmdDispacher, m_actionExecutor);
    RETURN_IF_NULL_WITHOUT_VALUE(m_pRFFreqscan);
}

//�ͷŸ��汾�����ҵ���߼�����ģ��
void CRFControlMediator::ReleaseDiffBLL()
{
    IRFAction* pRFActions[] =
    {
        m_pRFFreqscan,
        m_pRFCfgalm,
        m_pRFAtpc,
        m_pRFAnten
    };

    static const WORD size = COUNTOF(pRFActions);
    for (WORD i = 0; i < size; i++)
    {
        delete pRFActions[i];
    }

    m_pRFFreqscan = NULL;
    m_pRFCfgalm = NULL;
    m_pRFAtpc = NULL;
    m_pRFAnten = NULL;
}
