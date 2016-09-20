#include "wlan_virtual_board.h"
#include "wlan_dev_if.h"
#include "dump_if.h"

WORD CWlanVirtualBoard::GetBid()
{
    return m_wBid;
}

//��ȡwlan�豸������Ϣ
ST_DEV_BASE_INFO & CWlanVirtualBoard::GetDevBaseInfo()
{
    return m_devBaseInfo;
}

//��������˿�
void CWlanVirtualBoard::AssociatedVirtualPort(IWlanVirtualPort * pWlanVirtualPort)
{
    m_pWlanVirtualPort = pWlanVirtualPort;
}

//��ȡwlan�豸
IWlanDev * CWlanVirtualBoard::GetWlanDev()
{
    return m_pWlanDev;
}


void CWlanVirtualBoard::Dump(CDumpTool &dumpTool)
{
}

void CWlanVirtualBoard::CreateWlanDev()
{
    m_pWlanDev = ::CreateWlanDev();
}

CWlanVirtualBoard::CWlanVirtualBoard(WORD wBid, E_WLAN_MODE eMode, ST_DEV_BASE_INFO & devBaseInfo)
    : m_wBid(wBid), m_eMode(eMode), m_devBaseInfo(devBaseInfo)
{
    CreateWlanDev();
}


CWlanVirtualBoard::~CWlanVirtualBoard()
{
    DELETE_OBJECT(m_pWlanDev);
}