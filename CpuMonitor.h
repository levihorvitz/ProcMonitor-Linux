#ifndef CPU_MONITOR_H
#define CPU_MONITOR_H

#include <unistd.h>
#include <string>

long getProcessCpuTime(pid_t pid);
long getTotalCpuTime();
double calculateCpuUsage(pid_t pid, int delay_ms = 100);

#endif // CPU_MONITOR_H
