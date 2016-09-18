#pragma once
#include "wlan_dev_service_if.h"
#include "command_if.h"
#include "event_source.h"
#include "event_listener_if.h"

class ActiveObjectEngine;
class ThreadCreator;
class ScheduledCommand;
class CWlanDevProbe;

class CWlanDevService : public CEventSource, public IWlanDevService, public ICommand, public IEventListener
{
public:
    virtual bool initialize();

    // 通过 ICommand 继承
    virtual void Execute(CMessage * pMessage);

    // 通过 IEventListener 继承
    virtual WORD EventHandle(CMessage & message);

    virtual IWlanDev * GetWlanDev();
private:
    void InsmodWlanModule();
    bool InitService();
public:
    CWlanDevService();
    CWlanDevService(IWlanDev * pWlanDev);
    virtual ~CWlanDevService();

private:
    ScheduledCommand * m_pScheduleCmd;
    ActiveObjectEngine * m_pEngine;
    ThreadCreator * m_pThreadExec;
    CWlanDevProbe * m_pWlanDevProbe;
    IWlanDev * m_pWlanDev;

};