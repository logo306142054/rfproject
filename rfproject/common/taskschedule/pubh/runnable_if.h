#pragma once

class IRunnable
{
public:
    virtual void Run() = 0;
public:
    virtual ~IRunnable() {}
};