#include "../prih/rf_cmdlist.h"
#include "rf_err_def.h"

const WORD MAX_SIZE = 512;
//��������
WORD CRFCmdList::SendCmd(ST_CMDPACKAGE &stCmdPackage, COutStream &resulStream)
{
    if (MAX_SIZE == m_cmdsList.size())
    {
        return RF_ERR_COMMUN_BUSY;
    }

    CCmdPackage cmdPackage;
    CopyContext(stCmdPackage, cmdPackage);
    if (stCmdPackage.m_isUrGent)
    {
        m_urGentCmdsList.push_back(cmdPackage);
    }
    else
    {
        m_cmdsList.push_back(cmdPackage);
    }

    return CMDERR_SUCCESS;
}

//����������л�ȡ����
bool CRFCmdList::GetCmd(CCmdPackage &cmdPackage)
{
    CmdsList &cmdsList = !m_urGentCmdsList.empty() ? m_urGentCmdsList : m_cmdsList;

    if (!cmdsList.empty())
    {
        VOS_memcpy_s(&cmdPackage, sizeof(CCmdPackage), &cmdsList.front(), sizeof(CCmdPackage));
        cmdsList.pop_front();

        return true;
    }

    return false;
}

//�ж�ָ��byPortID�Ķ����Ƿ�Ϊ��
bool CRFCmdList::IsEmpty()
{
    bool bIsEmpty = m_cmdsList.empty() && m_urGentCmdsList.empty();

    return bIsEmpty;
}

//����������
void CRFCmdList::ClearAllCmds()
{
    m_cmdsList.clear();
    m_urGentCmdsList.clear();
}

//��stCmdPackage�е����ݸ��Ƶ�cmdPackage��
void CRFCmdList::CopyContext(ST_CMDPACKAGE &stCmdPackage, CCmdPackage &cmdPackage)
{
    cmdPackage.SetCodeID(stCmdPackage.m_wCmdID);
    cmdPackage.SetPara(stCmdPackage.m_byParas, stCmdPackage.m_byParaLen);
    if (0 != stCmdPackage.m_extPara)
    {
        CmdPacketInfo *pCmdPacketInfo = reinterpret_cast<CmdPacketInfo *>(stCmdPackage.m_extPara);
        if (NULL != pCmdPacketInfo)
        {
            cmdPackage.SetCmdPacketInfo(*pCmdPacketInfo);
        }
    }
}

CRFCmdList::CRFCmdList()
{
    ClearAllCmds();
}


CRFCmdList::~CRFCmdList()
{
    ClearAllCmds();
}