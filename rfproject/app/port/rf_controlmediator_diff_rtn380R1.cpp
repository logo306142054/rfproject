#include "../prih/rf_controlmediator.h"

//初始化各版本差异的业务逻辑处理模块
void CRFControlMediator::InitDiffBLL()
{
    m_pRFSoftMgr = new CRFSoftMgr(m_byPortID, m_cmdDispacher, m_actionExecutor);
    RETURN_IF_NULL_WITHOUT_VALUE(m_pRFSoftMgr);
}

//释放各版本差异的业务逻辑处理模块
void CRFControlMediator::ReleaseDiffBLL()
{
    IRFAction* pRFActions[] =
    {
        m_pRFSoftMgr
    };

    static const WORD size = COUNTOF(pRFActions);
    for (WORD i = 0; i < size; i++)
    {
        delete pRFActions[i];
    }

    m_pRFSoftMgr = NULL;
}
