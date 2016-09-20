#pragma once

class IWlanManager;
class CmdPacketInfo;
class Mailbox;

class CWlanCmdCallback
{
private:
    void RegCmd();
    void UnRegCmd();
    static bool MailboxCallback(void *pThis, CmdPacketInfo * pCmdInfo, BYTE * pRespResult, WORD * pWRespLen);
public:
    CWlanCmdCallback(WORD wBid, Mailbox * pMailbox, IWlanManager * pApManager);
    virtual ~CWlanCmdCallback();

private:
    IWlanManager * m_pApManager;
    Mailbox *m_pMailbox;
    WORD m_wBid;
};