#ifndef _RF_OAM_H_
#define _RF_OAM_H_

#include "rf_business_logic_layer.h"

class CRFOam :
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
    CRFOam(BYTE byPortID);
    CRFOam(BYTE byPortID, CRFCmdDispatcher &, IRFActionExecutor &);
    virtual ~CRFOam();
};

#endif
