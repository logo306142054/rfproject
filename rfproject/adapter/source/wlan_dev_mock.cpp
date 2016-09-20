#include "define.h"
#include "../prih/wlan_dev_mock.h"
#include "wlan_base_info.h"
#include "memory.h"
#include "message.h"
#include "comm_stream.h"

IWlanDev* CreateWlanDev()
{
    return new CWlanDevMock();
}
void CWlanDevMock::Probe(WORD wCmdId)
{
    if (m_devInfos != NULL)
    {
        BYTE params[MAX_PARAMETER_LEN] = { 0 };
        CRtnOutStream outStream(params, sizeof(params));
        for (int i = 0; i < m_byDevNum; i++)
        {
            outStream << m_byDevNum;
            outStream << (BYTE)m_devInfos[i].m_eWlanName;
            outStream << (BYTE)m_devInfos[i].m_eWlanMode;
            outStream << m_devInfos[i].m_bSupportMaxUserNum;
        }
        CRtnInStream inStream(outStream.GetPara(), outStream.GetPos());
        TrigerEvent(CMessage(wCmdId, CMDERR_SUCCESS, &inStream, this));
    }
}

void CWlanDevMock::SetDevInfo(ST_DEV_BASE_INFO * devInfos, BYTE num)
{
    ReleaseDev();
    if (devInfos == NULL || num == 0)
    {
        return;
    }

    m_devInfos = new ST_DEV_BASE_INFO[num];
    memcpy_s(m_devInfos, sizeof(ST_DEV_BASE_INFO) * num, devInfos, sizeof(ST_DEV_BASE_INFO) * num);
    m_byDevNum = num;
}


void CWlanDevMock::ReleaseDev()
{
    if (m_devInfos != NULL)
    {
        delete[] m_devInfos;
        m_devInfos = NULL;
        m_byDevNum = 0;
    }
}

CWlanDevMock::CWlanDevMock()
{
    m_devInfos = NULL;
    m_byDevNum = 0;
}

CWlanDevMock::~CWlanDevMock()
{
    ReleaseDev();
}
