#include "../prih/wlan_virtual_rt_mode_board.h"
#include "comm_stream.h"
#include "comm_cmdcode.h"
#include "wlan_dev_if.h"
#include "dump_if.h"
bool CWlanVirtualRtModeBoard::Dispatch(WORD wCmdID, CRtnInStream &, CRtnOutStream &)
{
    return false;
}

bool CWlanVirtualRtModeBoard::Response(WORD wCmdID, WORD wError, CRtnInStream &)
{
    return false;
}

void CWlanVirtualRtModeBoard::Dump(CDumpTool &)
{
}

CWlanVirtualRtModeBoard::CWlanVirtualRtModeBoard(WORD wBid, E_WLAN_MODE eMode, ST_DEV_BASE_INFO & devBaseInfo)
    : CWlanVirtualBoard(wBid, eMode, devBaseInfo)
{
}

CWlanVirtualRtModeBoard::~CWlanVirtualRtModeBoard()
{
}