#include "../prih/rf_prtclmgr_base.h"

//添加命令道队列中
WORD CRFPrtclMgrBase::AddCmd(ST_CMDPACKAGE &stCmdPackage, COutStream &resultOutStream)
{
    WORD wRet = m_cmdList.SendCmd(stCmdPackage, resultOutStream);
    if (CMDERR_SUCCESS == wRet)
    {
        NotifyNewCmd();
    }

    return wRet;
}

void CRFPrtclMgrBase::ClearAllCmds()
{
    m_cmdList.ClearAllCmds();
}

void CRFPrtclMgrBase::NotifyNewCmd()
{
    //发送newcmd事件
    CCmdPackage pack;
    if (!m_cmdList.GetCmd(pack))
    {
        return;
    }


    BYTE byPara[2] = { 0x4a, 0x0a };
    pack.SetPara(byPara, sizeof(byPara));
    //保存当前的命令信息
    pack.GetCmdPacketInfo(m_curCmdPacketInfo);

    CRFEvent event(NOTIFY_TR_CMD_RESPONSE, 0, &pack);
    TrigerEvent(event);
}

void CRFPrtclMgrBase::NotifyTRStatus(WORD wEventType)
{
    CRFEvent event(wEventType, 0, NULL);

    if (!m_bIsAllowToReportAlm)
    {
        event.m_wEventType = NOTIFY_TR_OFFLINE_NOT_REPORT_ALM;
    }
    else if (NOTIFY_TR_ONLINE == wEventType)
    {
        m_bIsAllowToReportAlm = true;
        m_wOfflineSecond = 0;
    }

    TrigerEvent(event);
}

//设置通信状态
void CRFPrtclMgrBase::SetCommunState(E_COMMUN_STATE eCommunState)
{
    m_eCommunState = eCommunState;
}

E_COMMUN_STATE CRFPrtclMgrBase::GetCommunState()
{
    return m_eCommunState;
}

CRFPrtclMgrBase::CRFPrtclMgrBase(BYTE byPortID)
{
    m_eCommunState = E_COMMUN_STATE_NORMAL;
    m_pCommunListener = NULL;
    m_curCmdPacketInfo.Zero();

    m_bIsAllowToReportAlm = true;
    m_wOfflineSecond = 0;
}


CRFPrtclMgrBase::~CRFPrtclMgrBase()
{
}
