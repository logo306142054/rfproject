#ifndef _RF_ASYNC_PRTCL_MGR_BASE_H_
#define _RF_ASYNC_PRTCL_MGR_BASE_H_

#include "rf_cmdlist.h"
#include "rf_eventsource_if.h"

class CRFPrtclMgrBase : public IRFEventSource
{
public:
    //������������
    WORD AddCmd(ST_CMDPACKAGE &, COutStream &);

    //����������
    void ClearAllCmds();

    //����ͨ��״̬
    void SetCommunState(E_COMMUN_STATE );

    //��ȡ��ǰͨ��״̬
    E_COMMUN_STATE GetCommunState();

    virtual void AddListener(class IRFEventListener *pListener){ m_pCommunListener = pListener; };

    virtual void AddListener(WORD, class IRFEventListener *){};

protected:
    virtual void TrigerEvent(CRFEvent &event)
    {
        if (NULL != m_pCommunListener)
        {
            m_pCommunListener->EventHandle(event);
        }
    }

private:
    void NotifyNewCmd();

    void NotifyTRStatus(WORD wEventType);
public:
    CRFPrtclMgrBase(BYTE byPortID);
    virtual ~CRFPrtclMgrBase();

private:
    CRFCmdList m_cmdList;
    CmdPacketInfo m_curCmdPacketInfo;
    E_COMMUN_STATE m_eCommunState;
    class IRFEventListener *m_pCommunListener;

    bool m_bIsAllowToReportAlm;
    WORD m_wOfflineSecond;
};

extern CRFPrtclMgrBase* GetPrtclMgrInstance(BYTE byPortID);

#endif
