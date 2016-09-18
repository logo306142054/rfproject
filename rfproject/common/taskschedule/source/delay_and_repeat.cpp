#include "define.h"
#include "delay_and_repeat.h"
#include "sleep_command.h"
#include "active_object_engine.h"

/** �Թ��캯���д����sleep time��ʼ����sleep״̬*/
void DelayAndRepeat::Sleep()
{
    Sleep(m_sleepTime);
}

/** �Ը�����sleep time��ʼ����sleep״̬*/
void DelayAndRepeat::Sleep(BYTE newSleepTime)
{
    if (m_pSleepOwn != nullptr)
    {
        m_pSleepOwn->SetSleepTime(newSleepTime);
        AddToEngine(*m_pSleepOwn);
    }
}

void DelayAndRepeat::AddToEngine(ICommand & cmd)
{
    m_engine.AddCommand(cmd);
}

/**�Ƿ��ӳ�ָ��ʱ��֮����ִ�����m_delayTime<=0��ʾ���ӳ�,ֱ�ӿ�ʼ*/
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
/*delayTime �ӳ�ָ��ʱ��֮��ſ�ʼִ��
  sleepTime ÿ��ִ��֮�����sleep״̬��ʱ�䣬��ÿ����ִ�м����ʱ��
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