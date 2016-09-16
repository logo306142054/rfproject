#include "delay_and_repeat.h"
#include "sleep_command.h"
#include "active_object_engine.h"

/** 以构造函数中传入的sleep time开始进入sleep状态*/
void DelayAndRepeat::Sleep()
{
    Sleep(m_sleepTime);
}

/** 以给定的sleep time开始进入sleep状态*/
void DelayAndRepeat::Sleep(BYTE newSleepTime)
{
    if (m_pSleepOwn != nullptr)
    {
        m_pSleepOwn->SetSleepTime(newSleepTime);
        AddToEngine(*m_pSleepOwn);
    }
}

void DelayAndRepeat::AddToEngine(Command & cmd)
{
    m_engine.AddCommand(cmd);
}

/**是否延迟指定时间之后再执行命令：m_delayTime<=0表示不延迟,直接开始*/
bool DelayAndRepeat::IsExecWithoutDelay()
{
    return m_delayTime <= 0;
}

void DelayAndRepeat::AddToEngineWithoutDelay()
{
    m_pSleepOwn = new SleepCommand(m_sleepTime, m_engine, *this);
    AddToEngine(*this);
}

void DelayAndRepeat::AddToEngineWithDelay()
{
    m_pSleepOwn = new SleepCommand(m_delayTime, m_engine, *this);
    AddToEngine(*m_pSleepOwn);
}
/*delayTime 延迟指定时间之后才开始执行
  sleepTime 每次执行之后进入sleep状态的时间，即每两次执行间隔的时间
  */
DelayAndRepeat::DelayAndRepeat(BYTE delayTime, BYTE sleepTime, ActiveObjectEngine& engine)
    : m_delayTime(delayTime),
    m_sleepTime(sleepTime),
    m_engine(engine)
{
    if (IsExecWithoutDelay())
    {
        AddToEngineWithoutDelay();
    }
    else
    {
        AddToEngineWithDelay();
    }
}

DelayAndRepeat::DelayAndRepeat(BYTE sleepTime, ActiveObjectEngine& engine)
    : DelayAndRepeat(0, sleepTime, engine)
{

}

DelayAndRepeat::~DelayAndRepeat()
{
    if (m_pSleepOwn != nullptr) {
        delete m_pSleepOwn;
        m_pSleepOwn = nullptr;
    }
}