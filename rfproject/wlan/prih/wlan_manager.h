#pragma once
#include "wlan_manager_if.h"
#include <list>

struct ST_WLAN_BASE_INFO;
class IWlanVirtualModeBoard;
class CWlanCmdCallback;
class Mailbox;

class CWlanManager : public IWlanManager
{
public:
    virtual void CmdDispath(WORD wBid, CmdPacketInfo * pCmdInfo, CRtnOutStream &);
    virtual bool initialize(WORD wBid, BYTE byVirtualBoardNum);
private:
    void InitVirtulBoard(ST_WLAN_BASE_INFO & stBaseInfo);
public:
    CWlanManager(ST_WLAN_BASE_INFO & stBaseInfo);
    virtual ~CWlanManager();

private:
    CWlanCmdCallback * m_pCmdCallBack;
    Mailbox * m_pMailbox;
    std::list<IWlanVirtualModeBoard *> m_virtualBoards;
    ST_WLAN_BASE_INFO & m_stBaseInfo;
    WORD m_wBid;
};