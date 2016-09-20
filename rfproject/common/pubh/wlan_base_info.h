#pragma once

enum E_WLAN_NAME
{
    WLAN_INVALID = 0,
    WLAN0,
    WLAN1,
    WLAN2
};

const WORD BOARD_ID_TO_DEV_NAME[][2]
{
    { 2, WLAN0 },
    { 3, WLAN1 },
    { 4, WLAN2 },
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

static WORD GetBidByDevName(E_WLAN_NAME eName)
{
    static const size_t size = sizeof(BOARD_ID_TO_DEV_NAME) / sizeof(BOARD_ID_TO_DEV_NAME[0]);
    for (size_t i = 0; i < size; i++)
    {
        if (eName == BOARD_ID_TO_DEV_NAME[i][1])
        {
            return BOARD_ID_TO_DEV_NAME[i][0];
        }
    }
    return 0;
}

static E_WLAN_NAME GetDevNameByBid(WORD wBid)
{
    static const size_t size = sizeof(BOARD_ID_TO_DEV_NAME) / sizeof(BOARD_ID_TO_DEV_NAME[0]);
    for (size_t i = 0; i < size; i++)
    {
        if (wBid == BOARD_ID_TO_DEV_NAME[i][0])
        {
            return (E_WLAN_NAME)BOARD_ID_TO_DEV_NAME[i][1];
        }
    }
    return WLAN_INVALID;
}