#ifndef _RF_DPD_H_
#define _RF_DPD_H_

#include "wlan_business_logic_layer.h"

class CRFDpd : public CApBLL
{
public:

    //����ַ�
    virtual bool Dispatch(WORD wCmdID, CRtnInStream &, CRtnOutStream &);

    //��Ӧ�������
    virtual bool Response(WORD wCmdID, WORD wError, CRtnInStream &);

    //ִ��Action����(ȡ���۲���ģʽ�е�update())
    virtual void Execute(CMessage *);

    //dumpģ���ڴ����
    virtual void Dump(CDumpTool &);

public:
    CRFDpd(BYTE byPortID);
    CRFDpd(BYTE byPortID, CRFCmdDispatcher &, IActionExecutor &);
    virtual ~CRFDpd();
};

#endif
