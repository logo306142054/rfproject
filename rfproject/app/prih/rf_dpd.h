#ifndef _RF_DPD_H_
#define _RF_DPD_H_

#include "rf_business_logic_layer.h"

class CRFDpd :
    public CRFBLL
{
public:
    //�����Ҫ���յ�����
    virtual void AddCmd(CRFCmdDispatcher &);

    //����ַ�
    virtual bool Dispatch(WORD wCmdID, CInStream &, COutStream &);

    //��Ӧ�������
    virtual bool Response(WORD wCmdID, WORD wError, CInStream &);

    //ִ��Action����(ȡ���۲���ģʽ�е�update())
    virtual void Receive(CRFEvent &);

    //dumpģ���ڴ����
    virtual void Dump(CDumpTool &);

public:
    CRFDpd(BYTE byPortID);
    CRFDpd(BYTE byPortID, CRFCmdDispatcher &, IRFActionExecutor &);
    virtual ~CRFDpd();
};

#endif
