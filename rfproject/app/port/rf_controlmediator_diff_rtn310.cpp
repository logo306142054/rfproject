#include "../prih/rf_controlmediator.h"

//��ʼ�����汾�����ҵ���߼�����ģ��
void CRFControlMediator::InitDiffBLL()
{
    m_pRFDpd = new CRFDpd(m_byPortID, m_cmdDispacher, m_actionExecutor);
    RETURN_IF_NULL_WITHOUT_VALUE(m_pRFDpd);

}

//�ͷŸ��汾�����ҵ���߼�����ģ��
void CRFControlMediator::ReleaseDiffBLL()
{
    ICommand* pRFActions[] =
    {
        m_pRFDpd,
    };
    
    static const WORD size = COUNTOF(pRFActions);
    for (WORD i = 0; i < size; i++)
    {
        delete pRFActions[i];
    }

    m_pRFDpd = NULL;
}
