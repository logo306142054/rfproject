#include "define.h"
#include "../prih/wlan_manager.h"
#include "comm_stream.h"
#include "../prih/wlan_cmd_callback.h"
#include "wlan_base_info.h"
#include "wlan_dev_service.h"
#include "message.h"

using namespace std;

#define LIST_VIRTUAL_BOARD list<IWlanVirtualBoard *>

void CWlanManager::CmdDispath(WORD wBid, CmdPacketInfo * pCmdInfo, CRtnOutStream &resOutStream)
{

}

WORD CWlanManager::EventHandle(CMessage & message)
{
    switch (message.m_wMessageId)
    {
        case EVENT_PROBED_NEW_DEV:
        {
            bool isSucess = InitVirtulBoard(*(static_cast<ST_DEV_BASE_INFO*>( message.m_pMessageData )));
            message.m_wError = isSucess ? ERR_VOS_SUCCESS : ERR_VOS_ERR;
            break;
        }
    }
  
    return ERR_VOS_SUCCESS;
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

bool CWlanManager::InitVirtulBoard(ST_DEV_BASE_INFO & stBaseInfo)
{
    const E_WLAN_NAME eName = GetDevNameByBid(m_wBid);
    if (stBaseInfo.m_eWlanName == eName)
    {
        //TODO
        printf("build or update virtual board by dev info\n");
        return true;
    }

    return false;
}

CWlanManager::CWlanManager() 
{

}

CWlanManager::~CWlanManager()
{
}


