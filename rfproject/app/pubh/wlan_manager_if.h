#pragma once

class CmdPacketInfo;
class CRtnOutStream;

class IWlanManager
{
public:
    virtual void CmdDispath(WORD wBid, CmdPacketInfo * pCmdInfo, CRtnOutStream &) = 0;
public:
    virtual ~IWlanManager() {}
};