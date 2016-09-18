#include "../prih/wlan_dev_probe.h"
#include "event_source_if.h"
#include "wlan_dev_service_if.h"
#include "wlan_dev_if.h"
#include "comm_cmdcode.h"
#include "comm_stream.h"
#include "message.h"

using namespace std;

//上线前探测的最大次数
const BYTE MAX_PROBE_NUM = 3;

void CWlanDevProbe::Execute(CMessage *)
{
    //未上线
    if (!IsCommunNormal())
    {
        ProbeDev();
    }

    Sleep();
}

bool CWlanDevProbe::IsCommunNormal()
{
    if (devs.empty())
    {
        return false;
    }

    list<DEV_STATE>::iterator itor = devs.begin();
    while (itor != devs.end())
    {
        if ((*itor).estate == E_ABNORMAL)
        {
            return false;
        }
        itor++;
    }

    return true;
}

void CWlanDevProbe::ProbeDev()
{
    IWlanDev* dev = m_pWlanDevService->GetWlanDev();
    if (dev != NULL)
    {
        dev->Probe(CMD_PROBE_DEV);
    }
}

CWlanDevProbe::CWlanDevProbe(BYTE delayTime, BYTE sleepTime, ActiveObjectEngine & engine, IWlanDevService * pWlanDevService)
    : DelayAndRepeat(delayTime, sleepTime, engine)
{
    m_pWlanDevService = pWlanDevService;
}


void CWlanDevProbe::Dump(CDumpTool & dump)
{
    std::list<DEV_STATE>::iterator itor = devs.begin();
    while (itor != devs.end())
    {
        printf("dump : devname=%d,isLoading=%d, byState=%d, m_byProbeNum=%d\n",
            (*itor).devInfo.m_eWlanName, (*itor).isLoading, (*itor).estate, (*itor).m_byProbeCount);
        itor++;
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
        printf(" probe dev name=%d, count=%d\n", existDev->devInfo.m_eWlanName, existDev->m_byProbeCount);
        if (existDev->m_byProbeCount == MAX_PROBE_NUM)
        {
            existDev->estate = E_NORMAL;
            printf(" prove dev success name=%d\n", existDev->devInfo.m_eWlanName);
            
            IEventSource * es = dynamic_cast<IEventSource*>(m_pWlanDevService);
            if (es != NULL)
            {
                es->TrigerEvent(CMessage(EVENT_PROBED_NEW_DEV, 0, &dev));
            }
        }
    }
    else
    {
        DEV_STATE newDev;
        newDev.m_byProbeCount = 0;
        newDev.isLoading = false;
        newDev.estate = E_ABNORMAL;
        newDev.devInfo = dev;
        devs.push_back(newDev);
        printf(" probe new dev name=%d\n", newDev.devInfo.m_eWlanName);
    }
}

DEV_STATE* CWlanDevProbe::GetDevFromList(E_WLAN_NAME eName)
{
    list<DEV_STATE>::iterator itor = devs.begin();
    while (itor != devs.end())
    {
        if ((*itor).devInfo.m_eWlanName == eName)
        {
            return &(*itor);
        }
        itor++;
    }

    return NULL;
}

CWlanDevProbe::~CWlanDevProbe()
{
    m_pWlanDevService = NULL;
}