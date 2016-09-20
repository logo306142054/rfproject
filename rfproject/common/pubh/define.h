#ifndef _DEFINE_H_
#define _DEFINE_H_

#include "stdlib.h"
#include "assert.h"
#include <vector>
#include <list>
#include <map>
#include "comm_type_def.h"


#define ACTION_ID WORD
const WORD ACTION_ALL = 0xff;

const WORD EVENT_PROBED_NEW_DEV = 0x0001;


#define ERR_VOS_SUCCESS 0
#define ERR_VOS_ERR 1
#define CMDERR_SUCCESS 0
#define CMDERR_ERR 1
#define COUNTOF(array) (sizeof(array) / (sizeof(array[0])))
#define RTN_ASSERT(obj) assert(obj)
#define VOS_memcpy_s memcpy_s
#define VOS_Output printf

#define DELETE_OBJECT(obj)\
    if(NULL != obj)\
    {\
        delete obj;\
        obj = NULL;\
    }

#define RETURN_FALSE_IF_POINTER_EQUAL_NULL(obj)\
    if(NULL == obj)\
    {\
        RTN_ASSERT(obj);\
        return false;\
    }

#define RETURN_NULL_IF_POINTER_EQUAL_NULL(obj)\
    if(NULL == obj)\
    {\
        RTN_ASSERT(obj);\
        return NULL;\
    }

#define RETURN_NOTHING_IF_POINTER_EQUAL_NULL(obj)\
    if(NULL == obj)\
    {\
        RTN_ASSERT(obj);\
        return;\
    }

#define RETURN_ERR_CODE_IF_POINTER_EQUAL_NULL(obj, err)\
    if(NULL == obj)\
    {\
        RTN_ASSERT(obj);\
        return err;\
    }

#define MAX_PORT 2
#define MIN_PORT 1

#define AP_LOG_INFO(msg) printf msg;

#define AP_LOG_ERR(msg) printf msg;

const WORD NOTIFY_TR_ONLINE = 1;
const WORD NOTIFY_TR_OFFLINE = 2;
const WORD NOTIFY_TR_CMD_RESPONSE = 3;
const WORD NOTIFY_TR_OFFLINE_NOT_REPORT_ALM = 4;

typedef enum
{
    E_COMMUN_STATE_UPGRADING,    //TR升级
    E_COMMUN_STATE_FLASH_TESTING,//flash测试
    E_COMMUN_STATE_NORMAL,       //通信正常
    E_COMMUN_STATE_INTERRUPTED        //通信失败
}E_COMMUN_STATE;

const WORD MAX_PARAMETER_LEN = 512;
struct ST_CMDPACKAGE
{
public:
    WORD m_wCmdID;
    BYTE m_byParaLen;
    BYTE m_byParas[MAX_PARAMETER_LEN];
    bool m_isNeedWaitResp;
    bool m_isUrGent;
    DWORD m_extPara;
public:
    ST_CMDPACKAGE(WORD wCmdID, BYTE byParaLen = 0, BYTE *pbyPara = NULL,
        bool isNeedWaitResp = true, bool isUrGent = false, DWORD extPara = 0)
    {
        m_wCmdID = wCmdID;
        m_byParaLen = byParaLen;
        if (NULL != pbyPara)
        {
            (void)VOS_memcpy_s(m_byParas, MAX_PARAMETER_LEN, pbyPara, byParaLen);
        }
        m_isNeedWaitResp = isNeedWaitResp;
        m_isUrGent = isUrGent;
        m_extPara = extPara;
    }
};

class Mailbox
{
public:
    Mailbox() {}
    ~Mailbox() {}
};

class IBase
{
public:
    virtual bool initialize() = 0;
    virtual ~IBase() {}
};
static WORD VOS_W2BY(WORD wSrc, BYTE* pbyDir)
{
    if (pbyDir == NULL)
    {
        return CMDERR_ERR;
    }
    pbyDir[0] = wSrc >> 8;
    pbyDir[1] = wSrc & 0x00FF;
    return 0;
}

static WORD VOS_BY2W(BYTE* pbySrc, WORD *wDir)
{
    if (pbySrc == NULL)
    {
        return CMDERR_ERR;
    }
    *wDir = (pbySrc[0] << 8) | pbySrc[1];
    return 0;
}

static WORD VOS_DW2BY(DWORD dwSrc, BYTE* pbyDir)
{
    if (pbyDir == NULL)
    {
        return CMDERR_ERR;
    }
    pbyDir[0] = (dwSrc & 0xFF000000) >> 24;
    pbyDir[1] = (dwSrc & 0x00FF0000) >> 16;
    pbyDir[2] = (dwSrc & 0x0000FF00) >> 8;
    pbyDir[3] = (dwSrc & 0x000000FF);
    return 0;
}
static WORD VOS_BY2DW(BYTE* pbySrc, DWORD *dwDir)
{
    if (pbySrc == NULL)
    {
        return CMDERR_ERR;
    }
    *dwDir = (pbySrc[0] << 24) | (pbySrc[1] << 16) | (pbySrc[2] << 8) | pbySrc[3];
    return 0;
}

class CmdPacketInfo
{
public:
    CmdPacketInfo() { wCMDID = 0; }

    WORD GetCMDID()
    {
        return wCMDID;
    }

    void Zero()
    {
        wCMDID = 0;
    }
public:
    WORD wCMDID;
};
#endif