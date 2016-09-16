#include "define.h"
#include "../prih/wlan_manager.h"
#include "comm_stream.h"
#include "../prih/wlan_cmd_callback.h"
#include "wlan_base_info.h"

using namespace std;

#define LIST_VIRTUAL_BOARD list<IWlanVirtualModeBoard *>;

void CWlanManager::CmdDispath(WORD wBid, CmdPacketInfo * pCmdInfo, CRtnOutStream &resOutStream)
{

}

//µ¥°å
bool CWlanManager::initialize(WORD wBid, BYTE byVirtualBoardNum)
{
    m_wBid = wBid;

    return false;
}

void CWlanManager::InitVirtulBoard(ST_WLAN_BASE_INFO & stBaseInfo)
{
   // if()
}

CWlanManager::CWlanManager(ST_WLAN_BASE_INFO & stBaseInfo)
{

}

CWlanManager::~CWlanManager()
{
}
