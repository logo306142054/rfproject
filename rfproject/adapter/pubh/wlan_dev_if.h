#pragma once

class IWlanDev 
{
public:
    virtual void Probe(WORD wCmdId) = 0;
public:
    virtual ~IWlanDev() {}
};

extern IWlanDev* CreateWlanDev();