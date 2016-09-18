// rfproject.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <iostream>
#include <iomanip>
#include "wlan/prih/rf_controlmediator.h"
#include "wlan/prih/wlan_manager.h"
#include "wlan_dev_service.h"
#include "adapter/prih/wlan_dev_mock.h"
#include "wlan_base_info.h"

using namespace std;


ST_DEV_BASE_INFO baseInfo[] =
{
    { WLAN0, AP_MODE, 20 },
    { WLAN1, AP_MODE, 20 },
    { WLAN2, RT_MODE, 1 }
};

void test_dev_probe_failed()
{
    CWlanDevMock * dev = new CWlanDevMock();


    dev->SetDevInfo(baseInfo, COUNTOF(baseInfo));
    CWlanDevService *m_pWlanDevService = new CWlanDevService(dev);

    CWlanManager *manager = new CWlanManager();
    manager->initialize(2, m_pWlanDevService);

    int _i;
    cin >> _i;

    delete manager;
    delete dev;
    delete m_pWlanDevService;
    

}
int _tmain(int argc, _TCHAR* argv[])
{
    test_dev_probe_failed();

    int _i;
    cin >> _i;

    

	return 1;
}

