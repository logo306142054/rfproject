// rfproject.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <iostream>
#include <iomanip>
#include "app/prih/rf_controlmediator.h"
#include "cmdpackage.h"

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
    BYTE byPortID = 1;
    CRFControlMediator mediator(byPortID);

    BYTE byPara[2] = { 2, 3 };
    CInStream instream(byPara, sizeof(byPara));
    COutStream outStream;
    mediator.HandleCmd(0x4f0a, instream, outStream);
    
    int _i;
    cin >> _i;
	return 1;
}

