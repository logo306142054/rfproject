#include "define.h"
#include "..\prih\wlan_cmd_callback.h"
#include "wlan_manager_if.h"
#include "comm_stream.h"

void CWlanCmdCallback::RegCmd()
{
}

void CWlanCmdCallback::UnRegCmd()
{
}

bool CWlanCmdCallback::MailboxCallback(void * pThis, CmdPacketInfo * pCmdInfo, BYTE * pRespResult, WORD * pwRespLen)
{
    CWlanCmdCallback & callback = *static_cast<CWlanCmdCallback*>(pThis);
    if (callback.m_pApManager != NULL)
    {
        CRtnOutStream resOutStream(pRespResult, MAX_PARAMETER_LEN);
        callback.m_pApManager->CmdDispath(callback.m_wBid, pCmdInfo, resOutStream);
    }

    return true;
}

CWlanCmdCallback::CWlanCmdCallback(WORD wBid, Mailbox * pMailbox, IWlanManager * pApManager) 
    : m_wBid(wBid), m_pMailbox(pMailbox), m_pApManager(pApManager)
{
}

CWlanCmdCallback::~CWlanCmdCallback()
{
}
