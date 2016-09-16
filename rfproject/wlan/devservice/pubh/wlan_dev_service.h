#pragma once
#include "wlan_dev_service_if.h"
#include "eventsource.h"

class CWlanDevService : public CEventSource, public IWlanDevService
{
public:
    virtual bool initialize();
public:
    CWlanDevService();
    virtual ~CWlanDevService();
};