#pragma once
#include "wlan_business_logic_layer_if.h"

class IWlanDev;
struct ST_DEV_BASE_INFO;
class IWlanVirtualPort;

class IWlanVirtualBoard : public IWlanBLL
{
public:
    virtual WORD GetBid() = 0;

    //获取wlan设备基本信息
    virtual ST_DEV_BASE_INFO & GetDevBaseInfo() = 0;

    //关联虚拟端口
    virtual void AssociatedVirtualPort(IWlanVirtualPort *) = 0;

    //获取wlan设备
    virtual IWlanDev * GetWlanDev() = 0;

    //命令分发，返回true表示不再由其他CmdHandler处理，否则该命令将继续分发给其他CmdHandler处理
    virtual bool Dispatch(WORD wCmdID, CRtnInStream &, CRtnOutStream &) = 0;

    //响应命令处理结果，返回true表示不再由其他CmdHandler处理，否则该命令将继续分发给其他CmdHandler处理
    virtual bool Response(WORD wCmdID, WORD wError, CRtnInStream &) = 0;

    //dump模块内存变量
    virtual void Dump(CDumpTool &) = 0;
public:
    virtual ~IWlanVirtualBoard() {}
};