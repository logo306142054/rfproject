#ifndef _RF_CMD_HANDLER_IF_H_
#define _RF_CMD_HANDLER_IF_H_

class IRFCmdHandler
{
public:
    ~IRFCmdHandler(){}

    //�����Ҫ���յ�����
    virtual void AddCmd(class CRFCmdDispatcher &) = 0;

    //����ַ�������true��ʾ����������CmdHandler�����������������ַ�������CmdHandler����
    virtual bool Dispatch(WORD wCmdID, CInStream &, COutStream &) = 0;

    //��Ӧ�������������true��ʾ����������CmdHandler�����������������ַ�������CmdHandler����
    virtual bool Response(WORD wCmdID, WORD wError, CInStream &) = 0;

};

#endif