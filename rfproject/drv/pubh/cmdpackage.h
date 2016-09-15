#ifndef _CCMD_PACKAGE_H_
#define _CCMD_PACKAGE_H_

#include "define.h"

class CCmdPackage
{
public:
    void SetCodeID(WORD wCodeID)
    {
        this->wCodeID = wCodeID;
    }

    WORD GetCodeID()
    {
        return wCodeID;
    }

    void SetPara(BYTE *pbyPara, WORD wParaLen)
    {
        if (NULL == pbyPara || wParaLen == 0)
        {
            m_wParaLen = 0;
            return;
        }
        m_wParaLen = wParaLen;
        memcpy(m_byPara, pbyPara, wParaLen);
    }

    void GetPara(BYTE **pbyPara, WORD *wParaLen)
    {
        if (0 != m_wParaLen)
        {
            *pbyPara = m_byPara;
            *wParaLen = m_wParaLen;
            return;
        }

        wParaLen = 0;
        *pbyPara = NULL;
    }

    void SetErrorCode(WORD wError)
    {
        this->wError = wError;
    }

    WORD GetErrorCode()
    {
        return wError;
    }

    void SetCmdPacketInfo(CmdPacketInfo &packetInfo)
    {
        VOS_memcpy_s(&m_packetInfo, sizeof(CmdPacketInfo), &packetInfo, sizeof(CmdPacketInfo));
    }

    void GetCmdPacketInfo(CmdPacketInfo &packetInfo)
    {
        VOS_memcpy_s(&packetInfo, sizeof(CmdPacketInfo), &m_packetInfo, sizeof(CmdPacketInfo));
    }

    CCmdPackage()
    {
        wCodeID = 0;
        m_wParaLen = 0;
        wError = 0;
        memset(m_byPara, 0, sizeof(m_byPara));
    }
    ~CCmdPackage()
    {
    }

private:
    WORD wCodeID;
    BYTE m_byPara[512];
    WORD m_wParaLen;
    WORD wError;
    CmdPacketInfo m_packetInfo;
};

#endif