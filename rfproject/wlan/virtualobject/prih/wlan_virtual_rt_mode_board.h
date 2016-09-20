#pragma once
#include "wlan_virtual_board.h"

class CWlanVirtualRtModeBoard : public CWlanVirtualBoard
{
public:
    // Í¨¹ý CWlanVirtualBoard ¼Ì³Ð
    virtual bool Dispatch(WORD wCmdID, CRtnInStream &, CRtnOutStream &);
    virtual bool Response(WORD wCmdID, WORD wError, CRtnInStream &);

    virtual void Dump(CDumpTool &);
public:
    CWlanVirtualRtModeBoard(WORD wBid, E_WLAN_MODE eMode, ST_DEV_BASE_INFO & debBaseInfo);
    virtual ~CWlanVirtualRtModeBoard();
};