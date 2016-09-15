#ifndef _RF_ATPC_H_
#define _RF_ATPC_H_

#include "rf_business_logic_layer.h"

class CRFAtpc :
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
    CRFAtpc(BYTE byPortID);
    CRFAtpc(BYTE byPortID, CRFCmdDispatcher &, IRFActionExecutor &);
    virtual ~CRFAtpc();
};

#endif