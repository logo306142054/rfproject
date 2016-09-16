#ifndef _AP_BLL_IF_H_
#define _AP_BLL_IF_H_

#include "define.h"
#include "ap_cmd_dispatcher.h"
#include "dump_if.h"
#include "command_if.h"

class IActionExecutor;

class IWlanBLL : public ICmdHandler, public ICommand, public IDump
{
public:

    //����ַ�������true��ʾ����������CmdHandler�����������������ַ�������CmdHandler����
    virtual bool Dispatch(WORD wCmdID, CRtnInStream &, CRtnOutStream &) = 0;

    //��Ӧ�������������true��ʾ����������CmdHandler�����������������ַ�������CmdHandler����
    virtual bool Response(WORD wCmdID, WORD wError, CRtnInStream &) = 0;

    //ִ��Action
    virtual void Execute(CMessage *) = 0;

    //����Actionִ����
    virtual void SetActionExecutor(ACTION_ID, class IActionExecutor &) = 0;

    //dumpģ���ڴ����
    virtual void Dump(CDumpTool &) = 0;
public:
    virtual ~IWlanBLL(){};

};

#endif