#ifndef _DELAY_AND_REPEAT_H_
#define _DELAY_AND_REPEAT_H_
#include "command.h"
#include "define.h"

class ActiveObjectEngine;
class SleepCommand;

class DelayAndRepeat : public Command
{
public:
    virtual void Exectue() = 0;

public:
    DelayAndRepeat(BYTE delayTime, BYTE sleepTime, ActiveObjectEngine& engine);
    DelayAndRepeat(BYTE sleepTime, ActiveObjectEngine& engine);

    virtual ~DelayAndRepeat();

protected:
    /** �Թ��캯���д����sleep time��ʼ����sleep״̬*/
    void Sleep();
    /** �Ը�����sleep time��ʼ����sleep״̬*/
    void Sleep(BYTE newSleepTime);

private:
    bool IsExecWithoutDelay();
    void AddToEngine(Command & cmd);
    void AddToEngineWithoutDelay();
    void AddToEngineWithDelay();

protected:
    BYTE m_sleepTime;
    BYTE m_delayTime;
    ActiveObjectEngine & m_engine;
    SleepCommand *m_pSleepOwn;
};
#endif