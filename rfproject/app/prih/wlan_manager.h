#pragma once
#include "wlan_manager_if.h"
#include "wlan_cmd_callback.h"

class CWlanManager : public IWlanManager
{
public:
    virtual void CmdDispath(WORD wBid, CmdPacketInfo * pCmdInfo, CRtnOutStream &);

public:
    CWlanManager();
    virtual ~CWlanManager();
};