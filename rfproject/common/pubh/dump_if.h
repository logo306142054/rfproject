#ifndef _AP_DUMP_H_
#define _AP_DUMP_H_

class CDumpTool
{
public:
    CDumpTool() {}
    ~CDumpTool() {}
};

class IDump
{
public:
    virtual void Dump(CDumpTool &dump) = 0;
    virtual ~IDump() {}
};

#endif