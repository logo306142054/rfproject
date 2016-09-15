#ifndef _RF_CMDUTIL_H_
#define _RF_CMDUTIL_H_

#include "define.h"
#include "rf_communication_if.h"

class CRFCmdUtil
{
public:
    //设置命令，带有命令参数，但无扩展参数
    static WORD SendCmd(BYTE byPortID, WORD wCmdID, BYTE byParaLen, BYTE *pbyPara, COutStream &resultOutStream);

    //查询命令，无命令参数，可能有扩展参数，异步通信需通过扩展参数判断是否需要给平台返回响应
    static WORD SendCmd(BYTE byPortID, WORD wCmdID, DWORD extPara, COutStream &resultOutStream);

    //由外部构造ST_CMDPACKAGE，命令信息自定义
    static WORD SendCmd(BYTE byPortID, ST_CMDPACKAGE &cmdPackage, COutStream &resultOutStream);

private:
    static IRFCommunicate* m_pRFCommunicate;
};

#endif