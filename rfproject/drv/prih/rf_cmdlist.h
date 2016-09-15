#ifndef _RF_CMDSENDER_H_
#define _RF_CMDSENDER_H_

#include "cmdpackage.h"

#define CmdsList std::list<CCmdPackage>

class CRFCmdList
{
public:
    //发送命令
    WORD SendCmd(ST_CMDPACKAGE &stCmdPackage, COutStream &);

    //从命令队列中获取命令
    bool GetCmd(CCmdPackage &);

    //判断指定byPortID的队列是否为空
    bool IsEmpty();

    //清除指定byPortID的命令队列
    void ClearAllCmds();

private:
    void CopyContext(ST_CMDPACKAGE &, CCmdPackage &);
public:
    CRFCmdList();
    ~CRFCmdList();

private:
    CmdsList m_cmdsList; //非紧急队列
    CmdsList m_urGentCmdsList; //紧急队列
};

#endif

