#pragma once
#include "wlan_virtual_port_if.h"

class CWlanVirtualPort : public IWlanVirtualPort
{
public:
    // 通过 IWlanVirtualPort 继承
    virtual IWlanVirtualBoard * GetAssociatedVirtualBoard();
    virtual IWlanDev * GetWlanDev();

    virtual bool Dispatch(WORD wCmdID, CRtnInStream &, CRtnOutStream &);
    virtual bool Response(WORD wCmdID, WORD wError, CRtnInStream &);
    virtual void Dump(CDumpTool &);
private:
    virtual void CreateWlanDev();
private:
    //不实现
    virtual void Execute(CMessage *) {}
    virtual void SetActionExecutor(ACTION_ID, IActionExecutor &) {}

public:
    CWlanVirtualPort(IWlanVirtualBoard *);
    virtual ~CWlanVirtualPort();

private:
    IWlanVirtualBoard * m_pAssociatedVirtualBoard;
    IWlanDev * m_pWlanDev;
};

