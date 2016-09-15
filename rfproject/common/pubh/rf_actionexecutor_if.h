#ifndef _RF_ACTIOON_EXECUTOR_IF_H_
#define _RF_ACTIOON_EXECUTOR_IF_H_

#include "rf_event.h"
#include "rf_action_if.h"

typedef enum 
{
    ACTIONID_LOOP = 1,
    ACTIONID_MUTE,
    ACTIONID_DPD,
    ACTIONID_FREQSCAN,
    ACTIONID_CFGALM,
    ACTIONID_MAINCFG,
    ACTIONID_SOFTMGR,
    ACTIONID_FADING,
    ACTIONID_ANTEN,
    ACTIONID_ATPC,
    ACTIONID_ACM,
    ACTIONID_OAM,
    ACTIONID_NOTIFY,
    ACTIONID_ALMPER,
    ACTIONID_ALL, //������Action����ָ��
}EN_ACTIONID;


class IRFActionExecutor
{
public:
    //���Action
    virtual void AddAction(EN_ACTIONID eActionID, IRFAction *action) = 0;

    //��ָ����Action����ָ��
    virtual void Execute(EN_ACTIONID eActionID, CRFEvent &event) = 0;

    //������Action����ָ��
    virtual void Execute(CRFEvent &event) = 0;

    virtual ~IRFActionExecutor(){}
};

#endif