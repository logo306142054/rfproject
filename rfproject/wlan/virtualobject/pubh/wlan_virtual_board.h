#pragma once
#include "wlan_virtual_board_if.h"
#include "wlan_base_info.h"

class CWlanVirtualBoard : public IWlanVirtualBoard
{
public:

    virtual WORD GetBid();

    //��ȡwlan�豸������Ϣ
    virtual ST_DEV_BASE_INFO & GetDevBaseInfo();

    //��������˿�
    virtual void AssociatedVirtualPort(IWlanVirtualPort *);

    //��ȡwlan�豸
    virtual IWlanDev * GetWlanDev();

    //dumpģ���ڴ����
    virtual void Dump(CDumpTool &);

    //����ַ�������true��ʾ����������CmdHandler�����������������ַ�������CmdHandler����
    virtual bool Dispatch(WORD wCmdID, CRtnInStream &, CRtnOutStream &) = 0;

    //��Ӧ�������������true��ʾ����������CmdHandler�����������������ַ�������CmdHandler����
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

