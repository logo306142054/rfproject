#pragma once
#include "define.h"

class CRtnInStream
{
public:
    CRtnInStream(BYTE *pbyPara, WORD wLen)
    {
        m_pbyParas = pbyPara;
        this->wLen = wLen;
        m_wPos = 0;
    }
    ~CRtnInStream() {}

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

    CRtnInStream& operator >> (WORD &wPara)
    {
        if (m_wPos >= wLen) RTN_ASSERT(0);
        VOS_BY2W(m_pbyParas + m_wPos, &wPara);
        m_wPos += sizeof(wPara);
        return *this;
    }

    CRtnInStream& operator >> (BYTE &byPara)
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

class CRtnOutStream
{
public:
    CRtnOutStream(BYTE *pByParas, WORD wLen)
    {
        m_byParas = pByParas;
        memset(m_byParas, 0, wLen);
        this->wLen = wLen;
        wPos = 0;
    }

    CRtnOutStream()
    {
        const WORD maxLen = 512;
        m_byParas = new BYTE[maxLen];
        memset(m_byParas, 0, sizeof(m_byParas) * maxLen);
        wLen = maxLen;
        wPos = 0;
    }
    ~CRtnOutStream() {}

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

    CRtnOutStream& operator << (WORD wPara)
    {
        VOS_W2BY(wPara, m_byParas + wPos);
        wPos += sizeof(wPara);
        return *this;
    }

    CRtnOutStream& operator << (BYTE byPara)
    {
        *(m_byParas + wPos) = byPara;
        wPos += sizeof(byPara);
        return *this;
    }

private:
    BYTE *m_byParas;
    WORD wLen;
    WORD wPos;
};
class CFoBuf
{
public:
    CFoBuf() {}
    char* test;
};
