#ifndef _ACTIOON_EXECUTOR_H_
#define _ACTIOON_EXECUTOR_H_


#include "define.h"
#include "actionexecutor_if.h"
#include "command_if.h"

#define ActionsMap std::map<ACTION_ID, ICommand*> 
#define MAP_KEY(map_iterator) ((map_iterator).first)
#define MAP_VALUE(map_iterator) ((map_iterator).second)

class CActionExecutor : public IActionExecutor
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
    void AddAction(ACTION_ID eActionID, ICommand *action)
    {
        m_actionsMap.insert(m_actionsMap.end(), std::pair<ACTION_ID, ICommand*>(eActionID, action));
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
    *       void Receive(CRFEvent &message)
    *       {
    *           if(NOTIFY_CFGALM_SETPOWER == event.m_wEventType)
    *           {
    *               ...
    *           }
    *       }
    *   };
    */
    virtual void Post(ACTION_ID actionId, CMessage &message)
    {
        if (ACTION_ALL == actionId)
        {
            Post(message);
            return;
        }
        for (ActionsMap::iterator it = m_actionsMap.begin(); it != m_actionsMap.end(); it++)
        {
            if (MAP_KEY(*it) == actionId)
            {
                if (NULL != MAP_VALUE(*it))
                {
                    MAP_VALUE(*it)->Execute(&message);
                    return;
                }
                VOS_Output("execute:: Action is NULL\n");
                return;
            }
        }

        VOS_Output("execute:: could't find action\n");
    }

    //������Action����ָ��
    virtual void Post(CMessage &message)
    {
        for (ActionsMap::iterator it = m_actionsMap.begin(); it != m_actionsMap.end(); it++)
        {
            if (NULL != MAP_VALUE(*it))
            {
                MAP_VALUE(*it)->Execute(&message);
            }
        }
    }

public:

    CActionExecutor()
    {
        m_actionsMap.clear();
    }

    virtual ~CActionExecutor()
    {
        m_actionsMap.clear();
    }

private:
    ActionsMap m_actionsMap;

};

#endif