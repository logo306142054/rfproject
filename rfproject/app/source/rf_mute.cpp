#include "../prih/rf_mute.h"

struct _ST_CMD_CALLBACK
{
    WORD wCmdID;
    void (CRFMute::*pFunCall)(CInStream &, COutStream &);
};
struct _ST_RESP_CALLBACK
{
    WORD wCmdID;
    void (CRFMute::*pFunCall)(WORD, CInStream &);
    bool bDoit;//表示此处处理完该命令后是否继续分发给其他模块处理，返回true直接停止，返回false则继续分发
#if 0
    _ST_RESP_CALLBACK(WORD wCmd, void (CRFMute::*pFCall)(WORD, CInStream &), bool doit = true)
    {
        wCmdID = wCmd;
        pFunCall = pFCall;
        bDoit = doit;
    }
#endif
};

//添加需要接收的命令
void CRFMute::AddCmd(CRFCmdDispatcher &rCmdDispacher)
{
    ST_CMDINFO stCmdInfos[] =
    {
        { 0x4f0A, 2, "CmdSetMute"},
    };
    rCmdDispacher.AddCmdHandler(this, stCmdInfos, COUNTOF(stCmdInfos));

    ST_CMDINFO stRespCmdInfos[] =
    {
        { 0x4f0A, NOT_FIXED_RESP_LEN },
    };
    rCmdDispacher.AddRespHandler(this, stRespCmdInfos, COUNTOF(stRespCmdInfos));
}

//命令分发
bool CRFMute::Dispatch(WORD wCmdID, CInStream &rParaInStream, COutStream &rResultOutStream)
{
    static const _ST_CMD_CALLBACK stCmdCallBack[] =
    {
        { 0x4f0A, &CRFMute::CmdSetMute },
    };
    static const BYTE byCount = COUNTOF(stCmdCallBack);
    for (BYTE i = 0; i < byCount; i++)
    {
        if (wCmdID == stCmdCallBack[i].wCmdID)
        {
            (this->*(stCmdCallBack[i].pFunCall))(rParaInStream, rResultOutStream);
            return true;
        }
    }
    
    return false;
}

//响应命令处理结果
bool CRFMute::Response(WORD wCmdID, WORD wError, CInStream &inStream)
{
    static const _ST_RESP_CALLBACK stRespCallBack[] = 
    {
        { 0x4f0a, &CRFMute::RespSetMute, true},
        { 0x4f0b, &CRFMute::RespGetMute, false},
    };
    static const BYTE byCount = COUNTOF(stRespCallBack);
    for (BYTE i = 0; i < byCount; i++)
    {
        if (wCmdID == stRespCallBack[i].wCmdID)
        {
            (this->*(stRespCallBack[i].pFunCall))(wError, inStream);
            return stRespCallBack[i].bDoit;
        }
    }
    
    return false;
}

//执行Action动作(取代观察者模式中的update())
void CRFMute::Receive(CRFEvent &event)
{

}

void CRFMute::CmdSetMute(CInStream &rParaInStream, COutStream &rResultOutStream)
{
    VOS_Output("mute::dispach id=[0x%x], paralen=%d\n", 0x4f0A, rParaInStream.GetLen());
    CRFCmdUtil::SendCmd(m_byPortID, 0x4f0A, (BYTE)(rParaInStream.GetLen()), rParaInStream.GetPara(), rResultOutStream);
}

void CRFMute::RespSetMute(WORD wError, CInStream &instream)
{
    VOS_Output("mute::response id=[0x%x], wError=%d, paralen=%d\n", 0x4f0a, wError, instream.GetLen());
    WORD wPara = 0;
    instream >> wPara;
    VOS_Output("wPara=%x\n", wPara);

    CRFEvent event(0x12, 0, NULL);
    Execute(event, ACTIONID_DPD);
}

void CRFMute::RespGetMute(WORD wError, CInStream &instream)
{
    VOS_Output("mute::response id=[0x%x], wError=%d, paralen=%d\n", 0x4f0b, wError, instream.GetLen());

    CRFEvent event(0x12, 0, NULL);
    Execute(event, ACTIONID_DPD);
}

void CRFMute::Dump(CDumpTool &dump)
{

}

CRFMute::CRFMute(BYTE byPortID) : CRFBLL(byPortID)
{

}

CRFMute::CRFMute(BYTE byPortID, CRFCmdDispatcher &rCmdDispacher, IRFActionExecutor &rActionExecutor)
    : CRFBLL(byPortID, rCmdDispacher, rActionExecutor)
{
    SetActionExecutor(ACTIONID_MUTE, rActionExecutor);
    AddCmd(rCmdDispacher);
}

CRFMute::~CRFMute()
{
}
