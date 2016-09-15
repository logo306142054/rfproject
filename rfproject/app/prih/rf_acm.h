#ifndef _RF_ACM_H_
#define _RF_ACM_H_

#include "rf_business_logic_layer.h"

class CRFAcm :
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
    CRFAcm(BYTE byPortID);
    CRFAcm(BYTE byPortID, CRFCmdDispatcher &, IRFActionExecutor &);
    virtual ~CRFAcm();
};

#endif 


