#ifndef _RF_CMDUTIL_H_
#define _RF_CMDUTIL_H_

#include "define.h"

class CRtnInStream;
class CRtnOutStream;

class CRFCmdUtil
{
public:
    //��������������������������չ����
    static WORD SendCmd(BYTE byPortID, WORD wCmdID, BYTE byParaLen, BYTE *pbyPara, CRtnOutStream &resultOutStream);

    //��ѯ����������������������չ�������첽ͨ����ͨ����չ�����ж��Ƿ���Ҫ��ƽ̨������Ӧ
    static WORD SendCmd(BYTE byPortID, WORD wCmdID, DWORD extPara, CRtnOutStream &resultOutStream);

    //���ⲿ����ST_CMDPACKAGE��������Ϣ�Զ���
    static WORD SendCmd(BYTE byPortID, ST_CMDPACKAGE &cmdPackage, CRtnOutStream &resultOutStream);

private:

};

#endif