#ifndef _RF_ASYNC_PRTCL_MGR_BASE_H_
#define _RF_ASYNC_PRTCL_MGR_BASE_H_

#include "rf_cmdlist.h"
#include "rf_eventsource_if.h"

class CRFPrtclMgrBase : public IRFEventSource
{
public:
    //添加命令到队列中
    WORD AddCmd(ST_CMDPACKAGE &, COutStream &);

    //清除命令队列
    void ClearAllCmds();

    //设置通信状态
    void SetCommunState(E_COMMUN_STATE );

    //获取当前通信状态
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
