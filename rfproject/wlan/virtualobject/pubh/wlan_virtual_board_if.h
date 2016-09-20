#pragma once
#include "wlan_business_logic_layer_if.h"

class IWlanDev;
struct ST_DEV_BASE_INFO;
class IWlanVirtualPort;

class IWlanVirtualBoard : public IWlanBLL
{
public:
    virtual WORD GetBid() = 0;

    //��ȡwlan�豸������Ϣ
    virtual ST_DEV_BASE_INFO & GetDevBaseInfo() = 0;

    //��������˿�
    virtual void AssociatedVirtualPort(IWlanVirtualPort *) = 0;

    //��ȡwlan�豸
    virtual IWlanDev * GetWlanDev() = 0;

    //����ַ�������true��ʾ����������CmdHandler�����������������ַ�������CmdHandler����
    virtual bool Dispatch(WORD wCmdID, CRtnInStream &, CRtnOutStream &) = 0;

    //��Ӧ�������������true��ʾ����������CmdHandler�����������������ַ�������CmdHandler����
    virtual bool Response(WORD wCmdID, WORD wError, CRtnInStream &) = 0;

    //dumpģ���ڴ����
    virtual void Dump(CDumpTool &) = 0;
public:
    virtual ~IWlanVirtualBoard() {}
};