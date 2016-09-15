#ifndef _RF_CMD_DISPACHER_H_
#define _RF_CMD_DISPACHER_H_

#include "rf_cmdhandler_if.h"

const WORD NOT_FIXED_RESP_LEN = 0;

#define DispatchersVector std::vector<ST_CMDREQUEST>

typedef struct _ST_CMDINFO
{
    WORD m_wCmdID;
    WORD m_wParasLen;
    char* pChCmdName;
}ST_CMDINFO;

class CRFCmdDispatcher
{
private:
    typedef struct _ST_CMDREQUEST
    {
    public:
        class IRFCmdHandler *m_pRFCmdhandler;
        ST_CMDINFO *m_stCmdInfo;
        WORD m_wCount;

        _ST_CMDREQUEST(class IRFCmdHandler *pRFCmdHandler, ST_CMDINFO *pStCmdInfo, WORD wCount)
        {
            m_pRFCmdhandler = pRFCmdHandler;
            m_stCmdInfo = new ST_CMDINFO[wCount];
            RTN_ASSERT(m_stCmdInfo);
            m_wCount = wCount;
            (void)VOS_memcpy_s(m_stCmdInfo, sizeof(ST_CMDINFO) * wCount, pStCmdInfo, sizeof(ST_CMDINFO) * wCount);
        }
    }ST_CMDREQUEST;

public:

    void AddCmdHandler(class IRFCmdHandler *pRFCmdHandler, ST_CMDINFO *pStCmdInfos, WORD wCount)
    {
        ST_CMDREQUEST stCmdRequest(pRFCmdHandler, pStCmdInfos, wCount);
        m_cmdDispatchers.push_back(stCmdRequest);
    }

    void AddRespHandler(class IRFCmdHandler *pRFCmdHandler, ST_CMDINFO *pStCmdInfos, WORD wCount)
    {
        for (WORD wIndex = 0; wIndex < wCount; wIndex++)
        {
            pStCmdInfos[wIndex].pChCmdName = NULL;
        }
        
        ST_CMDREQUEST stCmdResponse(pRFCmdHandler, pStCmdInfos, wCount);
        m_respDispatchers.push_back(stCmdResponse);
    }

    //分发平台下发的命令
    void CmdDispatch(WORD wCmdID, CInStream &paraInStream, COutStream &resultOutStream)
    {
        DispatchersVector::iterator it = m_cmdDispatchers.begin();
        bool bHasFound = false;
        ST_CMDINFO *pStCmdInfo = NULL;

        while (it != m_cmdDispatchers.end())
        {
            pStCmdInfo = (*it).m_stCmdInfo;
            if (NULL != pStCmdInfo)
            {
                for (WORD i = 0; i < (*it).m_wCount; i++)
                {
                    if (pStCmdInfo[i].m_wCmdID == wCmdID && NULL != (*it).m_pRFCmdhandler)
                    {
                        VOS_Output("name=%s\n", pStCmdInfo[i].pChCmdName);
                        if ((*it).m_pRFCmdhandler->Dispatch(wCmdID, paraInStream, resultOutStream))
                        {
                            return;
                        }
                        //返回false则继续查找下一个需要响应该命令的dispacher
                        bHasFound = true;
                        break;
                    }
                }
            }
            it++;
        }

        if (!bHasFound)
        {
            VOS_Output("RF CmdDispach:: Could't find cmdDispacher[0x%x]\n", wCmdID);
        }
        return;
    }

    void RespDispatch(WORD wCmdID, WORD wError, BYTE* pbyPara, WORD wRespParasLen)
    {
        DispatchersVector::iterator it = m_respDispatchers.begin();
        bool bHasFound = false;
        ST_CMDINFO *pStCmdInfo = NULL;
 
        while (it != m_respDispatchers.end())
        {
            pStCmdInfo = (*it).m_stCmdInfo;
            if (NULL == pStCmdInfo)
            {
                it++;
                continue;
            }
            for (WORD i = 0; i < (*it).m_wCount; i++)
            {
                //找到对应命令字
                if (pStCmdInfo[i].m_wCmdID == wCmdID)
                {
                    //判断响应参数的长度是否与预期的长度相等
                    bool bCheckCorrectly = (pStCmdInfo[i].m_wParasLen != NOT_FIXED_RESP_LEN) && 
                        ((pbyPara == NULL) || (wRespParasLen != pStCmdInfo[i].m_wParasLen));
                    if (bCheckCorrectly)
                    {
                        VOS_Output("RF RespDispach:: [0x%x] RespParaLen[%d] != FixedParaLen[%d].\n", 
                            wCmdID, wRespParasLen, pStCmdInfo[i].m_wParasLen);
                        return;
                    }
                    if (NULL == pbyPara)
                    {
                        //如果参数为空，则声明一个临时的数组，避免在创建paraInStream时被断言.
                        BYTE byTmp[1] = { 0 };
                        pbyPara = byTmp;
                        wRespParasLen = 0;
                    }
                    CInStream paraInStream(pbyPara, wRespParasLen);
                    if (NULL != (*it).m_pRFCmdhandler)
                    {
                        if ((*it).m_pRFCmdhandler->Response(wCmdID, wError, paraInStream))
                        {
                            return;
                        }
                        //返回false则继续查找下一个需要响应该命令的cmdhandler
                        bHasFound = true;
                        break;
                    }
                }
            }
            it++;
        }

        if (!bHasFound)
        {
            VOS_Output("RF RespDispatch:: Could't find RespDispatcher[0x%x]\n", wCmdID);
        }
        return;
    }

    void RegCmdInfoToUsp()
    {

    }

    void UnRegCmdInfoFromUsp()
    {

    }

private:
    inline void Release(DispatchersVector& dispatchers)
    {
        DispatchersVector::iterator it = dispatchers.begin();
        while (it != dispatchers.end())
        {
            if (NULL != (*it).m_stCmdInfo)
            {
                delete[] (*it).m_stCmdInfo;
                (*it).m_stCmdInfo = NULL;
            }
            it++;
        }
        dispatchers.clear();
    }

public:
    CRFCmdDispatcher()
    {
        Release(m_cmdDispatchers);
        Release(m_respDispatchers);
    }
    ~CRFCmdDispatcher()
    {
        Release(m_cmdDispatchers);
        Release(m_respDispatchers);
    }

private:
    DispatchersVector m_cmdDispatchers;
    DispatchersVector m_respDispatchers;
};

#endif