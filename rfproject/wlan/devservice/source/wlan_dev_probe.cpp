#include "../prih/wlan_dev_probe.h"
#include "event_source_if.h"
#include "wlan_dev_service_if.h"
#include "wlan_dev_if.h"
#include "comm_cmdcode.h"
#include "comm_stream.h"
#include "message.h"

using namespace std;

//上线前探测的最大次数
const BYTE MAX_PROBE_NUM = 2;

//TODO 对g_devs的访问应该做信号量互斥
LIST_DEV g_devs;

void CWlanDevProbe::Execute(CMessage *)
{
    ProbeDev();

    NotifyInitBoard();

    Sleep();
}

void CWlanDevProbe::ProbeDev()
{
    IWlanDev* dev = m_pWlanDevService->GetWlanDev();
    if (dev != NULL)
    {
        dev->Probe(CMD_PROBE_DEV);
    }
}

bool CWlanDevProbe::Dispatch(WORD wCmdID, CRtnInStream &, CRtnOutStream &)
{
    return false;
}

bool CWlanDevProbe::Response(WORD wCmdID, WORD wError, CRtnInStream &inStream)
{
    if (wCmdID == CMD_PROBE_DEV)
    {
        BYTE byDevNum = 0;
        BYTE byName = 0;
        BYTE byMode = 0;
        BYTE bySupportUserName = 0;
        inStream >> byDevNum;
        ST_DEV_BASE_INFO dev;
        for(int i = 0; i < byDevNum; i++)
        {
            inStream >> byName >> byMode >> bySupportUserName;
            dev.m_eWlanName = (E_WLAN_NAME)byName;
            dev.m_eWlanMode = (E_WLAN_MODE)byMode;
            dev.m_bSupportMaxUserNum = bySupportUserName;
            UpdateDevInfo(dev);
        }

        CheckDevState();
    }
    return false;
}

void CWlanDevProbe::UpdateDevInfo(ST_DEV_BASE_INFO &dev)
{
    DEV_STATE* existDev = GetDevFromList(dev.m_eWlanName);
    if (existDev != NULL)
    {
        existDev->m_byProbeCount = existDev->m_byProbeCount < MAX_PROBE_NUM ? existDev->m_byProbeCount + 1 : MAX_PROBE_NUM;
        existDev->devInfo = dev;
        //printf(" probe dev name=%d, count=%d\n", existDev->devInfo.m_eWlanName, existDev->m_byProbeCount);
        if (existDev->m_byProbeCount == MAX_PROBE_NUM)
        {
            existDev->eState = E_NORMAL;
            printf(" prove dev success name=%d\n", existDev->devInfo.m_eWlanName);
        }
    }
    else
    {
        DEV_STATE newDev;
        newDev.m_byProbeCount = 0;
        newDev.isLoading = false;
        newDev.eState = E_ABNORMAL;
        newDev.devInfo = dev;
        g_devs.push_back(newDev);
        printf(" probe new dev name=%d\n", newDev.devInfo.m_eWlanName);
    }
}

void CWlanDevProbe::NotifyInitBoard()
{
    if (g_devs.empty())
    {
        return;
    }

    IEventSource * es = dynamic_cast<IEventSource*>(m_pWlanDevService);
    RETURN_NOTHING_IF_POINTER_EQUAL_NULL(es);

    LIST_DEV::iterator itor = g_devs.begin();
    while (itor != g_devs.end())
    {
        if ((*itor).eState == E_NORMAL && !(*itor).isLoading)
        {
            CMessage msg(EVENT_PROBED_NEW_DEV, 0, &(*itor).devInfo);
            es->TrigerEvent(msg);

            if (msg.m_wError == ERR_VOS_SUCCESS)
            {
                (*itor).isLoading = true;
            }
        }
        itor++;
    }
}

void CWlanDevProbe::CheckDevState()
{
    LIST_DEV::iterator itor = g_devs.begin();
    while (itor != g_devs.end())
    {
        if ((*itor).eState == E_NORMAL)
        {
            (*itor).m_byProbeCount = (*itor).m_byProbeCount > 0 ? (*itor).m_byProbeCount - 1 : 0;
            if ((*itor).m_byProbeCount == 0)
            {
                (*itor).isLoading = false;
                (*itor).eState = E_ABNORMAL;
                //TODO 上报告警
            }
        }
        itor++;
    }
}

DEV_STATE* CWlanDevProbe::GetDevFromList(E_WLAN_NAME eName)
{
    LIST_DEV::iterator itor = g_devs.begin();
    while (itor != g_devs.end())
    {
        if ((*itor).devInfo.m_eWlanName == eName)
        {
            return &(*itor);
        }
        itor++;
    }

    return NULL;
}

void CWlanDevProbe::Dump(CDumpTool & dump)
{
    LIST_DEV::iterator itor = g_devs.begin();
    while (itor != g_devs.end())
    {
        printf("dump : devname=%d,isLoading=%d, byState=%d, m_byProbeNum=%d\n",
            (*itor).devInfo.m_eWlanName, (*itor).isLoading, (*itor).eState, (*itor).m_byProbeCount);
        itor++;
    }
}

CWlanDevProbe::CWlanDevProbe(BYTE delayTime, BYTE sleepTime, ActiveObjectEngine & engine, IWlanDevService * pWlanDevService)
    : DelayAndRepeat(delayTime, sleepTime, engine)
{
    m_pWlanDevService = pWlanDevService;
}

CWlanDevProbe::~CWlanDevProbe()
{
    m_pWlanDevService = NULL;
}