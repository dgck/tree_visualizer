#ifndef SYSINFO_H
#define SYSINFO_H

class SysInfo
{

public:

    SysInfo::SysInfo()
    {

    }
    SysInfo::~SysInfo()
    {

    }

    virtual void init() = 0;
    virtual double cpuLoadAverage() = 0;
    virtual double memoryUsed() = 0;
}


#endif // SYSINFO_H
