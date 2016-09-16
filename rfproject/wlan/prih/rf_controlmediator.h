#ifndef _RF_CONTROLL_MEDIATOR_H_
#define _RF_CONTROLL_MEDIATOR_H_

#include "rf_dpd.h"

#include "rf_controlmediator_if.h"
#include "rf_eventlistener_if.h"
#include "actionexecutor.h"
#include "wlan_manager_if.h"

class CRtnInStream;
class CRtnOutStream;

class CRFControlMediator : public IRFControlMediator, public IRFEventListener, public IDump
{
public:
    //����ƽ̨�·�������
    virtual void HandleCmd(WORD wCmdID, CRtnInStream &, CRtnOutStream &);

    //��������communication���ϱ����¼�
    virtual WORD EventHandle(CMessage &event);

    virtual void Dump(CDumpTool &);
private:
    //��ʼ��ҵ���߼�����ģ��
    void InitBLL();

    //��ʼ�����汾�����ҵ���߼�����ģ��
    void InitDiffBLL();

    //�ͷ�ҵ���߼�����ģ��
    void ReleaseBLL();

    //�ͷŸ��汾�����ҵ���߼�����ģ��
    void ReleaseDiffBLL();
public:
    CRFControlMediator(BYTE byPortID);
    virtual ~CRFControlMediator();

private:
  
    CRFDpd *m_pRFDpd;
    CRFCmdDispatcher m_cmdDispacher;
    CActionExecutor     m_actionExecutor;
    BYTE m_byPortID;
};

#endif

