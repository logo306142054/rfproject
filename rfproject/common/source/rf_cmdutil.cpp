#include "rf_cmdutil.h"
#include "comm_stream.h"

//设置命令，带有命令参数，但无扩展参数
WORD CRFCmdUtil::SendCmd(BYTE byPortID, WORD wCmdID, BYTE byParaLen, BYTE *pbyPara, CRtnOutStream &resultOutStream)
{
    ST_CMDPACKAGE cmdPackage(wCmdID, byParaLen, pbyPara);
    
    return SendCmd(byPortID, cmdPackage, resultOutStream);
}

//查询命令，无命令参数，可能有扩展参数，异步通信需通过扩展参数判断是否需要给平台返回响应
WORD CRFCmdUtil::SendCmd(BYTE byPortID, WORD wCmdID, DWORD extPara, CRtnOutStream &resultOutStream)
{
    ST_CMDPACKAGE cmdPackage(wCmdID);
    cmdPackage.m_extPara = extPara;

    return SendCmd(byPortID, cmdPackage, resultOutStream);
}

//由外部构造ST_CMDPACKAGE，命令信息自定义
WORD CRFCmdUtil::SendCmd(BYTE byPortID, ST_CMDPACKAGE &cmdPackage, CRtnOutStream &resultOutStream)
{
    VOS_Output("send Cmd 0x%x\n", cmdPackage.m_wCmdID);

    return 0;
}
