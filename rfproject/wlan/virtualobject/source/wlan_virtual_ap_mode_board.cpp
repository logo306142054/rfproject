#include "../prih/wlan_virtual_ap_mode_board.h"
#include "comm_stream.h"
#include "comm_cmdcode.h"
#include "wlan_dev_if.h"
#include "dump_if.h"

bool CWlanVirtualApModeBoard::Dispatch(WORD wCmdID, CRtnInStream &, CRtnOutStream &)
{
    return false;
}

bool CWlanVirtualApModeBoard::Response(WORD wCmdID, WORD wError, CRtnInStream &)
{
    return false;
}

void CWlanVirtualApModeBoard::Dump(CDumpTool &dumpTool)
{
}

CWlanVirtualApModeBoard::CWlanVirtualApModeBoard(WORD wBid, E_WLAN_MODE eMode, ST_DEV_BASE_INFO & devBaseInfo)
    : CWlanVirtualBoard(wBid, eMode, devBaseInfo)
{
}

CWlanVirtualApModeBoard::~CWlanVirtualApModeBoard()
{
}