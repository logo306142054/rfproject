#include "wlan_virtual_port.h"
#include "wlan_dev_if.h"
#include "dump_if.h"
#include "wlan_virtual_board_if.h"

IWlanVirtualBoard * CWlanVirtualPort::GetAssociatedVirtualBoard()
{
    return m_pAssociatedVirtualBoard;
}

IWlanDev * CWlanVirtualPort::GetWlanDev()
{
    return m_pWlanDev;
}

bool CWlanVirtualPort::Dispatch(WORD wCmdID, CRtnInStream &, CRtnOutStream &)
{
    return false;
}

bool CWlanVirtualPort::Response(WORD wCmdID, WORD wError, CRtnInStream &)
{
    return false;
}

void CWlanVirtualPort::Dump(CDumpTool &dumpToop)
{
}

void CWlanVirtualPort::CreateWlanDev()
{
    m_pWlanDev = ::CreateWlanDev();
}

CWlanVirtualPort::CWlanVirtualPort(IWlanVirtualBoard * pAssociatedVirtualBoard)
    : m_pAssociatedVirtualBoard(pAssociatedVirtualBoard)
{
}


CWlanVirtualPort::~CWlanVirtualPort()
{
    m_pAssociatedVirtualBoard = NULL;
    DELETE_OBJECT(m_pWlanDev);
}

