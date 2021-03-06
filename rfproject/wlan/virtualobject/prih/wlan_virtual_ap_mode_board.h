#pragma once
#include "wlan_virtual_board.h"

class CWlanVirtualApModeBoard : public CWlanVirtualBoard
{
public:
    // ͨ�� CWlanVirtualBoard �̳�
    virtual bool Dispatch(WORD wCmdID, CRtnInStream &, CRtnOutStream &);
    virtual bool Response(WORD wCmdID, WORD wError, CRtnInStream &);

    virtual void Dump(CDumpTool &);
public:
    CWlanVirtualApModeBoard(WORD wBid, E_WLAN_MODE eMode, ST_DEV_BASE_INFO & debBaseInfo);
    virtual ~CWlanVirtualApModeBoard();
};