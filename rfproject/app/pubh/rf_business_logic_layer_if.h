#ifndef _RF_BLL_IF_H_
#define _RF_BLL_IF_H_

#include "rf_action_if.h"
#include "rf_actionexecutor_if.h"
#include "../prih/rf_cmd_dispatcher.h"
#include "rf_dump_if.h"

class IRFBLL : public IRFCmdHandler, public IRFAction, public IRFDump
{
public:
    //�����Ҫ���յ�����
    virtual void AddCmd(class CRFCmdDispatcher &) = 0;

    //����ַ�������true��ʾ����������CmdHandler�����������������ַ�������CmdHandler����
    virtual bool Dispatch(WORD wCmdID, CInStream &, COutStream &) = 0;

    //��Ӧ�������������true��ʾ����������CmdHandler�����������������ַ�������CmdHandler����
    virtual bool Response(WORD wCmdID, WORD wError, CInStream &) = 0;

    //ִ��Action(ȡ���۲���ģʽ�е�update())
    virtual void Receive(CRFEvent &) = 0;

    //����Actionִ����
    virtual void SetActionExecutor(EN_ACTIONID, class IRFActionExecutor &) = 0;

    //dumpģ���ڴ����
    virtual void Dump(CDumpTool &) = 0;
public:
    virtual ~IRFBLL(){};

};

#endif