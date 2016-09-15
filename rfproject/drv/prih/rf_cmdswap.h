#ifndef _RF_CMD_SWAP_H_
#define _RF_CMD_SWAP_H_

struct ST_CMDS
{
    WORD wBSCmdID;
    WORD wTRCmdID;
};

// TODO��������Ҫת����������
const ST_CMDS stAllCmds[] = 
{
    {0x4f01, 0x4f03},
    {0x4f02, 0x4f04}
};

static const WORD wCmdsCount = COUNTOF(stAllCmds); //ת����������ĳ���
static const bool bIsTR = 1; //��ǰRF���Ƿ�Ϊһ��ʽTR�豸

static WORD SwitchToTRCmd(WORD wBSCmdID)
{
    //����360��380�·��������Ҫ��BS������ת���ɶ�Ӧ��TR������
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
    //����360��380TR����Ӧ�����Ҫ��TR������ת���ɶ�Ӧ��BS������
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