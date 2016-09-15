#ifndef _RF_SOFTMGR_H_
#define _RF_SOFTMGR_H_

#include "rf_softmgr_if.h"
#include "rf_business_logic_layer.h"

class CRFSoftMgr : public IRFSoftMgr, public CRFBLL
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
    CRFSoftMgr(BYTE byPortID);
    CRFSoftMgr(BYTE byPortID, CRFCmdDispatcher &, IRFActionExecutor &);
    virtual ~CRFSoftMgr();
    
private:
    IRFActionExecutor *m_pRFActionExecutor; //actionִ����
    BYTE m_byPortID;  //�˿ں�
};

#endif
