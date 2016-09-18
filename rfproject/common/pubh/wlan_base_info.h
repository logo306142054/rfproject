#pragma once
#include "define.h"

enum E_WLAN_NAME
{
    WLAN0,
    WLAN1,
    WLAN2
};

enum E_WLAN_MODE
{
    AP_MODE,
    RELAY_MODE,
    RT_MODE
};

struct ST_DEV_BASE_INFO
{
    E_WLAN_NAME m_eWlanName;
    E_WLAN_MODE m_eWlanMode;
    BYTE m_bSupportMaxUserNum;
};