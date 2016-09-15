#ifndef _RF_DUMP_H_
#define _RF_DUMP_H_

class CDumpTool
{
public:
    CDumpTool(){}
    ~CDumpTool(){}
};

class IRFDump
{
public:
    virtual void Dump(CDumpTool &dump) = 0;
};

#endif