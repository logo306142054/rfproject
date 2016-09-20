#include "../prih/wlan_virtual_relay_mode_board.h"
#include "comm_stream.h"
#include "comm_cmdcode.h"
#include "wlan_dev_if.h"
#include "dump_if.h"

bool CWlanVirtualRelayModeBoard::Dispatch(WORD wCmdID, CRtnInStream &, CRtnOutStream &)
{
    return false;
}

bool CWlanVirtualRelayModeBoard::Response(WORD wCmdID, WORD wError, CRtnInStream &)
{
    return false;
}

void CWlanVirtualRelayModeBoard::Dump(CDumpTool &)
{
}

CWlanVirtualRelayModeBoard::CWlanVirtualRelayModeBoard(WORD wBid, E_WLAN_MODE eMode, ST_DEV_BASE_INFO & devBaseInfo)
    : CWlanVirtualBoard(wBid, eMode, devBaseInfo)
{
}

CWlanVirtualRelayModeBoard::~CWlanVirtualRelayModeBoard()
{
}
