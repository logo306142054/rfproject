#ifndef _RF_CMD_SWAP_H_
#define _RF_CMD_SWAP_H_

struct ST_CMDS
{
    WORD wBSCmdID;
    WORD wTRCmdID;
};

// TODO：补充需要转换的命令字
const ST_CMDS stAllCmds[] = 
{
    {0x4f01, 0x4f03},
    {0x4f02, 0x4f04}
};

static const WORD wCmdsCount = COUNTOF(stAllCmds); //转换命令数组的长度
static const bool bIsTR = 1; //当前RF侧是否为一体式TR设备

static WORD SwitchToTRCmd(WORD wBSCmdID)
{
    //对于360、380下发的命令，需要将BS命令字转换成对应的TR命令字
    if (bIsTR)
    {
        for each (ST_CMDS stCmds in stAllCmds)
        {
            if (stCmds.wBSCmdID == wBSCmdID)
            {
                return stCmds.wTRCmdID;
            }
        }
    }

    return wBSCmdID;
}

static WORD SwitchToBSCmd(WORD wTRCmdID)
{
    //对于360、380TR的响应命令，需要将TR命令字转换成对应的BS命令字
    if (bIsTR)
    {
        for each (ST_CMDS stCmds in stAllCmds)
        {
            if (stCmds.wTRCmdID == wTRCmdID)
            {
                return stCmds.wBSCmdID;
            }
        }
    }

    return wTRCmdID;
}

#endif