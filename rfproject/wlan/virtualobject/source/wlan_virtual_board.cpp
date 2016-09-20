#include "wlan_virtual_board.h"
#include "wlan_dev_if.h"
#include "dump_if.h"

WORD CWlanVirtualBoard::GetBid()
{
    return m_wBid;
}

//获取wlan设备基本信息
ST_DEV_BASE_INFO & CWlanVirtualBoard::GetDevBaseInfo()
{
    return m_devBaseInfo;
}

//关联虚拟端口
void CWlanVirtualBoard::AssociatedVirtualPort(IWlanVirtualPort * pWlanVirtualPort)
{
    m_pWlanVirtualPort = pWlanVirtualPort;
}

//获取wlan设备
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