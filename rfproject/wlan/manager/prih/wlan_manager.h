﻿#pragma once
#include "wlan_manager_if.h"
#include <list>
#include "event_listener_if.h"

struct ST_DEV_BASE_INFO;
class IWlanVirtualBoard;
class CWlanCmdCallback;
class Mailbox;
class IWlanDevService;

class CWlanManager : public IWlanManager, public IEventListener
{
public:
    virtual void CmdDispath(WORD wBid, CmdPacketInfo * pCmdInfo, CRtnOutStream &);
    virtual bool initialize(WORD wBid, IWlanDevService * pWlanDevService);

    // 通过 IEventListener 继承
    virtual WORD EventHandle(CMessage & message);

private:
    bool InitVirtulBoard(ST_DEV_BASE_INFO & stBaseInfo);
public:
    CWlanManager();
    virtual ~CWlanManager();

private:
    CWlanCmdCallback * m_pCmdCallBack;
    Mailbox * m_pMailbox;
    IWlanDevService * m_pWlanDevService;
    std::list<IWlanVirtualBoard *> m_virtualBoards;
    WORD m_wBid;
};