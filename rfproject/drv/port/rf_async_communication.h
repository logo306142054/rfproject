#ifndef _RF_COMMUNICATION_H_
#define _RF_COMMUNICATION_H_

#include "../prih/rf_prtclmgr_base.h"
#include "rf_eventsource.h"
#include "rf_communication_if.h"

class CRFCommunicate : public IRFCommunicate, public CRFEventSource, public IRFEventListener
{
public:
    static CRFCommunicate* GetInstance();
public:
    //��������
    virtual WORD SendCmd(BYTE byPortID, ST_CMDPACKAGE &, COutStream &);

    //����ͨ��״̬
    virtual void SetCommunState(BYTE byPortID, E_COMMUN_STATE );

    //���ָ��byPortID���������
    virtual void ClearAllCmds(BYTE byPortID);

    //����ϲ������
    virtual void AddListener(IRFEventListener *);

    //����prtclmgr�ϱ����¼�
    virtual WORD EventHandle(CRFEvent &event);

protected:
    //�жϵ�ǰ״̬���Ƿ������·�����
    virtual bool IsAllowToSendCmd(E_COMMUN_STATE , WORD wCmdID);

    virtual BYTE GetIndexByPortID(BYTE byPortID);

    //�Ը���������Ӧ�������Ԥ����
    virtual void HandleSpecialCmd();

private:
    //��ȡָ��byPortID��prtclmgr������
    CRFPrtclMgrBase *GetPrtclMgrReference(BYTE byPortID);

public:
    virtual ~CRFCommunicate();
private:
    //����ģʽ���������ⲿ���ù��캯��
    CRFCommunicate();
private:
    static CRFCommunicate* m_pRFCommunicate;   
    CRFPrtclMgrBase *m_pPrtclMgrs[MAX_PORT];
};

#endif
