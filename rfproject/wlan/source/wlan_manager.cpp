#include "define.h"
#include "../prih/wlan_manager.h"
#include "comm_stream.h"
#include "../prih/wlan_cmd_callback.h"
#include "wlan_base_info.h"
#include "wlan_dev_service.h"
#include "message.h"

using namespace std;

#define LIST_VIRTUAL_BOARD list<IWlanVirtualModeBoard *>;

const WORD BOARD_ID_TO_DEV_NAME[][2]
{
    { 2, WLAN0 },
    { 3, WLAN1 },
    { 4, WLAN1 },
};

void CWlanManager::CmdDispath(WORD wBid, CmdPacketInfo * pCmdInfo, CRtnOutStream &resOutStream)
{

}

WORD CWlanManager::EventHandle(CMessage & message)
{
    switch (message.m_wMessageId)
    {
        case EVENT_PROBED_NEW_DEV:
        {
            InitVirtulBoard(*(static_cast<ST_DEV_BASE_INFO*>( message.m_pMessageData )));
            break;
        }
    }
  
    return WORD();
}

//µ¥°å
bool CWlanManager::initialize(WORD wBid, IWlanDevService * pWlanDevService)
{
    m_wBid = wBid;
    m_pWlanDevService = pWlanDevService;

    CEventSource *es = dynamic_cast<CEventSource*>(m_pWlanDevService);
    if (es != NULL)
    {
        es->AddListener(EVENT_PROBED_NEW_DEV, this);
        printf("start listening dev probe event\n");
    }
    return false;
}

void CWlanManager::InitVirtulBoard(ST_DEV_BASE_INFO & stBaseInfo)
{
    for (size_t i = 0; i < sizeof(BOARD_ID_TO_DEV_NAME); i++)
    {
        if (stBaseInfo.m_eWlanName == BOARD_ID_TO_DEV_NAME[i][1] && m_wBid == BOARD_ID_TO_DEV_NAME[i][0])
        {
            m_pBaseInfo = &stBaseInfo;
            //TODO
            printf("build or update virtual board by dev info\n");
            return;
        }
    }
}

CWlanManager::CWlanManager() 
{

}

CWlanManager::~CWlanManager()
{
    DELETE_OBJECT(m_pWlanDevService);
}


