#ifndef _RF_CMDUTIL_H_
#define _RF_CMDUTIL_H_

#include "define.h"
#include "rf_communication_if.h"

class CRFCmdUtil
{
public:
    //��������������������������չ����
    static WORD SendCmd(BYTE byPortID, WORD wCmdID, BYTE byParaLen, BYTE *pbyPara, COutStream &resultOutStream);

    //��ѯ����������������������չ�������첽ͨ����ͨ����չ�����ж��Ƿ���Ҫ��ƽ̨������Ӧ
    static WORD SendCmd(BYTE byPortID, WORD wCmdID, DWORD extPara, COutStream &resultOutStream);

    //���ⲿ����ST_CMDPACKAGE��������Ϣ�Զ���
    static WORD SendCmd(BYTE byPortID, ST_CMDPACKAGE &cmdPackage, COutStream &resultOutStream);

private:
    static IRFCommunicate* m_pRFCommunicate;
};

#endif