#include "rf_cmdutil.h"

IRFCommunicate* CRFCmdUtil::m_pRFCommunicate = GetCommunicateInstance();

//��������������������������չ����
WORD CRFCmdUtil::SendCmd(BYTE byPortID, WORD wCmdID, BYTE byParaLen, BYTE *pbyPara, COutStream &resultOutStream)
{
    ST_CMDPACKAGE cmdPackage(wCmdID, byParaLen, pbyPara);
    
    return SendCmd(byPortID, cmdPackage, resultOutStream);
}

//��ѯ����������������������չ�������첽ͨ����ͨ����չ�����ж��Ƿ���Ҫ��ƽ̨������Ӧ
WORD CRFCmdUtil::SendCmd(BYTE byPortID, WORD wCmdID, DWORD extPara, COutStream &resultOutStream)
{
    ST_CMDPACKAGE cmdPackage(wCmdID);
    cmdPackage.m_extPara = extPara;

    return SendCmd(byPortID, cmdPackage, resultOutStream);
}

//���ⲿ����ST_CMDPACKAGE��������Ϣ�Զ���
WORD CRFCmdUtil::SendCmd(BYTE byPortID, ST_CMDPACKAGE &cmdPackage, COutStream &resultOutStream)
{
    RETURN_IF_NULL_WITH_VALUE(m_pRFCommunicate, CMDERR_ERR);
    VOS_Output("send Cmd 0x%x\n", cmdPackage.m_wCmdID);

    return m_pRFCommunicate->SendCmd(byPortID, cmdPackage, resultOutStream);
}
