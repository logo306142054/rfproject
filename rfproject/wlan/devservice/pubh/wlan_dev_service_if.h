#pragma once
#include "define.h"

class IWlanDev;

class IWlanDevService : public IBase
{
public:
    virtual IWlanDev * GetWlanDev() = 0;
public:
    virtual ~IWlanDevService() {}
};