#ifndef _RF_CMDSENDER_H_
#define _RF_CMDSENDER_H_

#include "cmdpackage.h"

#define CmdsList std::list<CCmdPackage>

class CRFCmdList
{
public:
    //��������
    WORD SendCmd(ST_CMDPACKAGE &stCmdPackage, COutStream &);

    //����������л�ȡ����
    bool GetCmd(CCmdPackage &);

    //�ж�ָ��byPortID�Ķ����Ƿ�Ϊ��
    bool IsEmpty();

    //���ָ��byPortID���������
    void ClearAllCmds();

private:
    void CopyContext(ST_CMDPACKAGE &, CCmdPackage &);
public:
    CRFCmdList();
    ~CRFCmdList();

private:
    CmdsList m_cmdsList; //�ǽ�������
    CmdsList m_urGentCmdsList; //��������
};

#endif

