#ifndef _AP_CMD_HANDLER_IF_H_
#define _AP_CMD_HANDLER_IF_H_

class CRtnInStream;
class CRtnOutStream;

class ICmdHandler
{
public:
    virtual ~ICmdHandler(){}

    //����ַ�������true��ʾ����������CmdHandler�����������������ַ�������CmdHandler����
    virtual bool Dispatch(WORD wCmdID, CRtnInStream &, CRtnOutStream &) = 0;

    //��Ӧ�������������true��ʾ����������CmdHandler�����������������ַ�������CmdHandler����
    virtual bool Response(WORD wCmdID, WORD wError, CRtnInStream &) = 0;

};

#endif