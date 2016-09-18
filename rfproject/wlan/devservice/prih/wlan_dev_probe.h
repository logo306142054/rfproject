#pragma once
#include "define.h"
#include "delay_and_repeat.h"
#include "wlan_base_info.h"
#include "cmd_handler_if.h"
#include "dump_if.h"

#include <list>

class IWlanDevService;

enum E_STATE
{
    E_ABNORMAL,
    E_NORMAL
};
struct DEV_STATE
{
    ST_DEV_BASE_INFO devInfo;
    bool isLoading;
    E_STATE estate;
    BYTE m_byProbeCount;
};

class CWlanDevProbe : public DelayAndRepeat, public ICmdHandler, public IDump
{
private:

public:
    // 通过 DelayAndRepeat 继承
    virtual void Execute(CMessage *);

    // 通过 ICmdHandler 继承
    virtual bool Dispatch(WORD wCmdID, CRtnInStream &, CRtnOutStream &);
    virtual bool Response(WORD wCmdID, WORD wError, CRtnInStream &);
    
    // 通过 IDump 继承
    virtual void Dump(CDumpTool & dump);

private:
    bool IsCommunNormal();
    void ProbeDev();

    void UpdateDevInfo(ST_DEV_BASE_INFO &dev);

    DEV_STATE* GetDevFromList(E_WLAN_NAME eName);

public:
    CWlanDevProbe(BYTE delayTime, BYTE sleepTime, ActiveObjectEngine & engine, IWlanDevService * pWlanDevService);
    virtual ~CWlanDevProbe();
    
private:
    
    IWlanDevService * m_pWlanDevService;
    std::list<DEV_STATE> devs;


};