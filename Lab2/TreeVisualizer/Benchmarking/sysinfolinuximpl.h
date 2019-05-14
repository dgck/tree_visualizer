#ifndef SYSINFOLINUXIMPL_H
#define SYSINFOLINUXIMPL_H

#include "sysinfo.h"
#include <sys/types.h>
#include <sys/sysinfo.h>

#include <QtGlobal>
#include <QFile>
#include <QVector>

/*

    как использовать это апи для замера сколько занмиает памяти и времени каждая функция
    - заиксировать занчение до и после

*/

class SysInfoLinuxImpl : public SysInfo
{
public:
    SysInfoLinuxImpl::SysInfoLinuxImpl() :
        SysInfo(),
        mCpuLoadLastValues()
    {

    }
    void SysInfoLinuxImpl::init()
    {
        mCpuLoadLastValues = cpuRawData();
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

    double SysInfoLinuxImpl::cpuLoadAverage()
    {
        QVector<qulonglong> firstSample = mCpuLoadLastValues;
        QVector<qulonglong> secondSample = cpuRawData();
        mCpuLoadLastValues = secondSample;
        double overall = (secondSample[0] - firstSample[0])
        + (secondSample[1] - firstSample[1])
        + (secondSample[2] - firstSample[2]);
        double total = overall + (secondSample[3] - firstSample[3]);
        double percent = (overall / total) * 100.0;
        return qBound(0.0, percent, 100.0);
    }

private:
    QVector<qulonglong> cpuRawData()
    {
        QFile file("/proc/stat");
        file.open(QIODevice::ReadOnly);
        QByteArray line = file.readLine();
        file.close();
        qulonglong totalUser = 0, totalUserNice = 0,
        totalSystem = 0, totalIdle = 0;

        std::sscanf(line.data(), "cpu %llu %llu %llu %llu",
        &totalUser, &totalUserNice, &totalSystem,
        &totalIdle);
        QVector<qulonglong> rawData;
        rawData.append(totalUser);
        rawData.append(totalUserNice);
        rawData.append(totalSystem);
        rawData.append(totalIdle);
        return rawData;

    }

    QVector<qulonglong> mCpuLoadLastValues;
};

#endif // SYSINFOLINUXIMPL_H
