#include "../prih/rf_controlmediator.h"
#include "comm_stream.h"

//初始化业务逻辑处理模块
void CRFControlMediator::InitBLL()
{
    InitDiffBLL();
}

//释放业务逻辑处理模块
void CRFControlMediator::ReleaseBLL()
{
    ReleaseDiffBLL();

}

//处理平台下发的命令
void CRFControlMediator::HandleCmd(WORD wCmdID, CRtnInStream &paraInStream, CRtnOutStream &resultOutStream)
{
     m_cmdDispacher.CmdDispatch(wCmdID, paraInStream, resultOutStream);
}

//处理来自communication层上报的事件
WORD CRFControlMediator::EventHandle(CMessage &message)
{

    return CMDERR_SUCCESS;
}

void CRFControlMediator::Dump(CDumpTool &dump)
{

}

CRFControlMediator::CRFControlMediator(BYTE byPortID)
{
    m_byPortID = byPortID;

    InitBLL();
}


CRFControlMediator::~CRFControlMediator()
{
    ReleaseBLL();
}
//初始化各版本差异的业务逻辑处理模块
void CRFControlMediator::InitDiffBLL()
{
    m_pRFDpd = new CRFDpd(m_byPortID, m_cmdDispacher, m_actionExecutor);
    RETURN_NOTHING_IF_POINTER_EQUAL_NULL(m_pRFDpd);

}

//释放各版本差异的业务逻辑处理模块
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