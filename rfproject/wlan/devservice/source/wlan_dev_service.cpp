#include "wlan_dev_service.h"
#include "active_object_engine.h"
#include "scheduled_command.h"
#include "thread_creator.h"
#include "../prih/wlan_dev_probe.h"
#include "comm_cmdcode.h"
#include "message.h"
#include "cmd_handler_if.h"
#include "wlan_dev_if.h"
#include "event_single_source_if.h"

bool CWlanDevService::initialize()
{
    InsmodWlanModule();

    m_pWlanDev = CreateWlanDev();
    RETURN_FALSE_IF_POINTER_EQUAL_NULL(m_pWlanDev);
    IEventSingleSource * iss = dynamic_cast<IEventSingleSource *>(m_pWlanDev);
    RETURN_FALSE_IF_POINTER_EQUAL_NULL(iss);

    iss->SetSingleListener(this);

    if (!InitService())
    {
        return false;
    }
    
    return true;
}

void CWlanDevService::InsmodWlanModule()
{
    printf("insmod wlan ko\n");
}

bool CWlanDevService::InitService()
{
    m_pEngine = new ActiveObjectEngine();
    RETURN_FALSE_IF_POINTER_EQUAL_NULL(m_pEngine);

    m_pScheduleCmd = new ScheduledCommand(dynamic_cast<ICommand*>(this), 5, 1, *m_pEngine);
    RETURN_FALSE_IF_POINTER_EQUAL_NULL(m_pScheduleCmd);

    m_pWlanDevProbe = new CWlanDevProbe(1, 1, *m_pEngine, this);

    m_pThreadExec = CreateNewThread(m_pEngine, "dev_service");
    RETURN_FALSE_IF_POINTER_EQUAL_NULL(m_pThreadExec);

    return true;
}

WORD CWlanDevService::EventHandle(CMessage & message)
{
    struct ST_CB
    {
        WORD wCmdId;
        ICmdHandler * pHandler;
    };

    const ST_CB cb[] = {
        { CMD_PROBE_DEV , m_pWlanDevProbe }
    };

    const BYTE bySize = COUNTOF(cb);
    for (BYTE i = 0; i < bySize; i++)
    {
        if (message.m_wMessageId == cb[i].wCmdId && cb[i].pHandler != NULL)
        {
            if (cb[i].pHandler->Response(message.m_wMessageId, message.m_wError, *(CRtnInStream*)(message.m_pMessageData)))
                return 0;
        }
    }

    return 0;
}

IWlanDev * CWlanDevService::GetWlanDev()
{
    return m_pWlanDev;
}

void CWlanDevService::Execute(CMessage *)
{
   // printf("execute\n");
}

CWlanDevService::CWlanDevService()
{
    initialize();
}

CWlanDevService::CWlanDevService(IWlanDev * pWlanDev)
{
    m_pWlanDev = pWlanDev;
    IEventSingleSource * iss = dynamic_cast<IEventSingleSource *>(m_pWlanDev);
    iss->SetSingleListener(this);

    InsmodWlanModule();
    InitService();
}

CWlanDevService::~CWlanDevService()
{
    m_pThreadExec->Stop();
    DELETE_OBJECT(m_pThreadExec);
    DELETE_OBJECT(m_pEngine);
    DELETE_OBJECT(m_pScheduleCmd);
    DELETE_OBJECT(m_pWlanDevProbe);
    DELETE_OBJECT(m_pWlanDev);
}