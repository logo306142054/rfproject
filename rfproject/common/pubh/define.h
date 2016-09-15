#ifndef _DEFINE_H_
#define _DEFINE_H_

#include "stdlib.h"
#include "assert.h"
#include <vector>
#include <list>
#include <map>

#define BYTE unsigned char
#define WORD unsigned short
#define DWORD unsigned int

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

#define RETURN_IF_NULL(obj)\
    if(NULL == obj)\
    {\
        RTN_ASSERT(obj);\
        return NULL;\
    }

#define RETURN_IF_NULL_WITHOUT_VALUE(obj)\
    if(NULL == obj)\
    {\
        RTN_ASSERT(obj);\
        return;\
    }

#define RETURN_IF_NULL_WITH_VALUE(obj, err)\
    if(NULL == obj)\
    {\
        RTN_ASSERT(obj);\
        return err;\
    }

#define MAX_PORT 2
#define MIN_PORT 1

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

class CInStream
{
public:
    CInStream(BYTE *pbyPara, WORD wLen)
    {
        m_pbyParas = pbyPara;
        this->wLen = wLen;
        m_wPos = 0;
    }
    ~CInStream(){}

    WORD GetLen()
    {
        return wLen;
    }

    WORD GetPos()
    {
        return m_wPos;
    }

    BYTE* GetPara()
    {
        return m_pbyParas;
    }

    CInStream& operator >> (WORD &wPara)
    {
        if (m_wPos >= wLen) RTN_ASSERT(0);
        VOS_BY2W(m_pbyParas + m_wPos, &wPara);
        m_wPos += sizeof(wPara);
        return *this;
    }

    CInStream& operator >> (BYTE &byPara)
    {
        if (m_wPos >= wLen) RTN_ASSERT(0);
        byPara = *(m_pbyParas + m_wPos);
        m_wPos += sizeof(byPara);
        return *this;
    }
private:
    WORD wLen;
    WORD m_wPos;
    BYTE *m_pbyParas;
};

class COutStream
{
public:
    COutStream()
    {
        memset(m_byParas, 0, sizeof(m_byParas));
        wLen = sizeof(m_byParas);
        wPos = 0;
    }
    ~COutStream(){}

    BYTE* GetPara()
    {
        return m_byParas;
    }

    WORD GetLen()
    {
        return wLen;
    }

    WORD GetPos()
    {
        return wPos;
    }

    COutStream& operator << (WORD wPara)
    {
        VOS_W2BY(wPara, m_byParas + wPos);
        wPos += sizeof(wPara);
        return *this;
    }

    COutStream& operator << (BYTE byPara)
    {
        *(m_byParas + wPos) = byPara;
        wPos += sizeof(byPara);
        return *this;
    }

private:
    BYTE m_byParas[512];
    WORD wLen;
    WORD wPos;
};
class CFoBuf
{
public:
    CFoBuf(){}
    char* test;
};

class CmdPacketInfo
{
public:
    CmdPacketInfo(){ wCMDID = 0; }

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