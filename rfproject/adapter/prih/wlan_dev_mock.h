#pragma once
#include "define.h"

#include "event_single_source.h"
#include "wlan_dev_if.h"

struct ST_DEV_BASE_INFO;

class CWlanDevMock : public CEventSingleSource, public IWlanDev
{
public:
    // Í¨¹ý IWlanDev ¼Ì³Ð
    virtual void Probe(WORD wCmdId);

    void SetDevInfo(ST_DEV_BASE_INFO *devInfos, BYTE num);

private:
    void ReleaseDev();
public:
    CWlanDevMock();
    ~CWlanDevMock();
private:
    ST_DEV_BASE_INFO *m_devInfos;
    BYTE m_byDevNum;
};