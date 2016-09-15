#ifndef _RF_MUTE_H_
#define _RF_MUTE_H_

#include "rf_business_logic_layer.h"

class CRFMute : public CRFBLL
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

private:
    void CmdSetMute(CInStream &, COutStream &);
    void RespSetMute(WORD wError, CInStream &instream);
    void RespGetMute(WORD wError, CInStream &instream);
public:
    CRFMute(BYTE byPortID);
    CRFMute(BYTE byPortID, CRFCmdDispatcher &, IRFActionExecutor &);
    virtual ~CRFMute();
};

#endif

