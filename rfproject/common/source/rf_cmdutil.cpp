#include "rf_cmdutil.h"
#include "comm_stream.h"

//��������������������������չ����
WORD CRFCmdUtil::SendCmd(BYTE byPortID, WORD wCmdID, BYTE byParaLen, BYTE *pbyPara, CRtnOutStream &resultOutStream)
{
    ST_CMDPACKAGE cmdPackage(wCmdID, byParaLen, pbyPara);
    
    return SendCmd(byPortID, cmdPackage, resultOutStream);
}

//��ѯ����������������������չ�������첽ͨ����ͨ����չ�����ж��Ƿ���Ҫ��ƽ̨������Ӧ
WORD CRFCmdUtil::SendCmd(BYTE byPortID, WORD wCmdID, DWORD extPara, CRtnOutStream &resultOutStream)
{
    ST_CMDPACKAGE cmdPackage(wCmdID);
    cmdPackage.m_extPara = extPara;

    return SendCmd(byPortID, cmdPackage, resultOutStream);
}

//���ⲿ����ST_CMDPACKAGE��������Ϣ�Զ���
WORD CRFCmdUtil::SendCmd(BYTE byPortID, ST_CMDPACKAGE &cmdPackage, CRtnOutStream &resultOutStream)
{
    VOS_Output("send Cmd 0x%x\n", cmdPackage.m_wCmdID);

    return 0;
}
