#include "sysinfo.h"

//strategy pattern
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
