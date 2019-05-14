#ifndef SYSINFOLINUXIMPL_H
#define SYSINFOLINUXIMPL_H

#include "sysinfo.h"
#include <sys/types.h>
#include <sys/sysinfo.h>

#include <QtGlobal>

class SysInfoLinuxImpl : public SysInfo
{
public:
    SysInfoLinuxImpl::SysInfoLinuxImpl() :
        SysInfo()
    {
    }

    double SysInfoLinuxImpl::memoryUsed()
    {
        struct sysinfo memInfo;
        sysinfo(&memInfo);
        qulonglong totalMemory = memInfo.totalram;
        totalMemory += memInfo.totalswap;
        totalMemory *= memInfo.mem_unit;
        qulonglong totalMemoryUsed = memInfo.totalram - memInfo.freeram;
        totalMemoryUsed += memInfo.totalswap - memInfo.freeswap;
        totalMemoryUsed *= memInfo.mem_unit;
        double percent = (double)totalMemoryUsed /
        (double)totalMemory * 100.0;
        return qBound(0.0, percent, 100.0);
    }
};

#endif // SYSINFOLINUXIMPL_H
