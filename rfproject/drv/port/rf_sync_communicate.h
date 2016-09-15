#ifndef _RF_COMMUNICATION_H_
#define _RF_COMMUNICATION_H_

#include "rf_communication_if.h"
#include "rf_eventsource.h"

class CRFCommunicate : public IRFCommunicate, public CRFEventSource
{
public:
    static CRFCommunicate* GetInstance();
public:
    //�������ͬ��ͨ�ŵ��豸���ڴ�ֱ�ӽ���Ӧ���������resultStream����
    virtual WORD SendCmd(BYTE byPortID, ST_CMDPACKAGE &, COutStream &);

    //����ͨ��״̬
    virtual void SetCommunState(BYTE byPortID, E_COMMUN_STATE );

    //����ϲ������
    virtual void AddListener(IRFEventListener *);

    //��ʵ�֣�ͬ��ͨ��δʹ���������
    virtual void ClearAllCmds(BYTE ){};

public:
    virtual ~CRFCommunicate();
private:
    //����ģʽ���������ⲿ���ù��캯��
    CRFCommunicate();

private:
    static CRFCommunicate* m_pRFCommunicate;
    E_COMMUN_STATE m_eCommunState;
};

#endif
