#ifndef _RF_CONTROLL_MEDIATOR_H_
#define _RF_CONTROLL_MEDIATOR_H_

#include "rf_loop.h"
#include "rf_mute.h"
#include "rf_acm.h"
#include "rf_anten.h"
#include "rf_atpc.h"
#include "rf_cfgalm.h"
#include "rf_dpd.h"
#include "rf_fademargin.h"
#include "rf_freqscan_base.h"
#include "rf_maincfg.h"
#include "rf_oam.h"
#include "rf_almper.h"
#include "rf_softmgr.h"
#include "rf_notify.h"

#include "rf_controlmediator_if.h"
#include "rf_eventlistener_if.h"
#include "rf_actionexecutor.h"

class CRFControlMediator : public IRFControlMediator, public IRFEventListener, public IRFDump
{
public:
    //����ƽ̨�·�������
    virtual void HandleCmd(WORD wCmdID, CInStream &, COutStream &);

    //��������communication���ϱ����¼�
    virtual WORD EventHandle(CRFEvent &event);

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
    CRFAcm  *m_pRFAcm;
    CRFAnten *m_pRFAnten;
    CRFAtpc *m_pRFAtpc;
    CRFCfgalm *m_pRFCfgalm;
    CRFDpd *m_pRFDpd;
    CRFFademargin *m_pRFFademargin;
    CRFFreqscanBase *m_pRFFreqscan;
    CRFMainCfg *m_pRFMaincfg;
    CRFLoop *m_pRFLoop;
    CRFMute *m_pRFMute;
    CRFOam *m_pRFOam;
    CRFAlmper *m_pRFAlmper;
    CRFSoftMgr *m_pRFSoftMgr;
    CRFNotify *m_pRFNotify;
    CRFCmdDispatcher m_cmdDispacher;
    CRFActionExecutor     m_actionExecutor;
    BYTE m_byPortID;
};

#endif

