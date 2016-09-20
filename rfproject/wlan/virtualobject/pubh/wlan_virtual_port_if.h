#pragma once
#include "wlan_business_logic_layer_if.h"

class IWlanDev;
class IWlanVirtualBoard;
class IWlanVirtualPort : public IWlanBLL
{
public:

    //��ȡ������������
    virtual IWlanVirtualBoard * GetAssociatedVirtualBoard() = 0;

    //��ȡwlan�豸
    virtual IWlanDev * GetWlanDev() = 0;

    //����ַ�������true��ʾ����������CmdHandler�����������������ַ�������CmdHandler����
    virtual bool Dispatch(WORD wCmdID, CRtnInStream &, CRtnOutStream &) = 0;

    //��Ӧ�������������true��ʾ����������CmdHandler�����������������ַ�������CmdHandler����
    virtual bool Response(WORD wCmdID, WORD wError, CRtnInStream &) = 0;

    //dumpģ���ڴ����
    virtual void Dump(CDumpTool &) = 0;
public:
    virtual ~IWlanVirtualPort() {}
};