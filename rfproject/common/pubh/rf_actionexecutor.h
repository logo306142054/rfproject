#ifndef _RF_ACTIOON_EXECUTOR_H_
#define _RF_ACTIOON_EXECUTOR_H_

#include "rf_actionexecutor_if.h"

#define ActionsMap std::map<EN_ACTIONID, IRFAction*> 
#define MAP_KEY(map_iterator) ((map_iterator).first)
#define MAP_VALUE(map_iterator) ((map_iterator).second)

class CRFActionExecutor : public IRFActionExecutor
{
public:

    /**
    *����˵��:���Action����ָ����action�󶨵�ActionID
    *��������:
    *   eActionID: ö��ֵ����action�󶨵�ID
    *   action   : IRFAction�ӿ�ʵ��
    *����ֵ:��
    *�÷�����:  
    *   CRFActionExecutor executor;
    *   IRFAction action = new Loop(byPortID);
    *   executor.AddAction(ACTIONID_LOOP, action);
    *
    */
    void AddAction(EN_ACTIONID eActionID, IRFAction *action)
    {
        m_actionsMap.insert(m_actionsMap.end(), std::pair<EN_ACTIONID, IRFAction*>(eActionID, action));
    }

    /**
    *����˵��:��ָ����ActionID����ָ��
    *��������:
    *   eActionID: ö��ֵ����action�󶨵�ID
    *   event   :  ��Ŵ˴�ָ��������Ϣ
    *����ֵ:��
    *�÷�����:
    *   CRFActionExecutor executor;
    *   IRFAction action = new CRFCfgAlm(byPortID);
    *   executor.AddAction(ACTIONID_CFGALM, action);
    *
    *   class CRFMainCfg
    *   {
    *       WORD RespSetPower()
    *       {
    *           CRFEvent event(NOTIFY_CFGALM_SETPOWER, CMDERR_SUCCESS, MWALM_OFF);
    *           executor.execute(ACTIONID_CFGALM, event);
    *       }
    *   };
    *
    *   class CRFCfgAlm
    *   {
    *       void Receive(CRFEvent &event)
    *       {
    *           if(NOTIFY_CFGALM_SETPOWER == event.m_wEventType)
    *           {
    *               ...
    *           }
    *       }
    *   };
    */
    virtual void Execute(EN_ACTIONID eActionID, CRFEvent &event)
    {
        if (ACTIONID_ALL == eActionID)
        {
            Execute(event);
            return;
        }
        for (ActionsMap::iterator it = m_actionsMap.begin(); it != m_actionsMap.end(); it++)
        {
            if (MAP_KEY(*it) == eActionID)
            {
                if (NULL != MAP_VALUE(*it))
                {
                    MAP_VALUE(*it)->Receive(event);
                    return;
                }
                VOS_Output("execute:: Action is NULL\n");
                return;
            }
        }

        VOS_Output("execute:: could't find action\n");
    }

    //������Action����ָ��
    virtual void Execute(CRFEvent &event)
    {
        for (ActionsMap::iterator it = m_actionsMap.begin(); it != m_actionsMap.end(); it++)
        {
            if (NULL != MAP_VALUE(*it))
            {
                MAP_VALUE(*it)->Receive(event);
            }
        }
    }

public:

    CRFActionExecutor()
    {
        m_actionsMap.clear();
    }

    virtual ~CRFActionExecutor()
    {
        m_actionsMap.clear();
    }

private:
    ActionsMap m_actionsMap;

};

#endif