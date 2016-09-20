#pragma once
#include "wlan_virtual_board_if.h"
#include "wlan_base_info.h"

class CWlanVirtualBoard : public IWlanVirtualBoard
{
public:

    virtual WORD GetBid();

    //获取wlan设备基本信息
    virtual ST_DEV_BASE_INFO & GetDevBaseInfo();

    //关联虚拟端口
    virtual void AssociatedVirtualPort(IWlanVirtualPort *);

    //获取wlan设备
    virtual IWlanDev * GetWlanDev();

    //dump模块内存变量
    virtual void Dump(CDumpTool &);

    //命令分发，返回true表示不再由其他CmdHandler处理，否则该命令将继续分发给其他CmdHandler处理
    virtual bool Dispatch(WORD wCmdID, CRtnInStream &, CRtnOutStream &) = 0;

    //响应命令处理结果，返回true表示不再由其他CmdHandler处理，否则该命令将继续分发给其他CmdHandler处理
    virtual bool Response(WORD wCmdID, WORD wError, CRtnInStream &) = 0;

protected:
    virtual void CreateWlanDev();
private:
    
    virtual void Execute(CMessage *) {}
    virtual void SetActionExecutor(ACTION_ID, IActionExecutor &) {}
public:
    CWlanVirtualBoard(WORD wBid, E_WLAN_MODE eMode, ST_DEV_BASE_INFO & devBaseInfo);
    virtual ~CWlanVirtualBoard();

private:
    WORD m_wBid;
    E_WLAN_MODE m_eMode;
    ST_DEV_BASE_INFO &m_devBaseInfo;
    IWlanVirtualPort * m_pWlanVirtualPort;
    IWlanDev * m_pWlanDev;
};

