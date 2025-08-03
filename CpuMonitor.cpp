#include "CpuMonitor.h"
#include <fstream>
#include <sstream>
#include <thread>
#include <chrono>

long getProcessCpuTime(pid_t pid) {
    std::ifstream stat("/proc/" + std::to_string(pid) + "/stat");
    if (!stat.is_open()) return 0;

    std::string line;
    std::getline(stat, line);
    std::istringstream iss(line);
    std::string token;
    long utime = 0, stime = 0;
    for (int i = 0; i < 13; ++i) iss >> token;
    iss >> utime >> stime;
    return utime + stime;
}

long getTotalCpuTime() {
    std::ifstream stat("/proc/stat");
    if (!stat.is_open()) return 0;

    std::string cpu;
    long user, nice, system, idle, iowait, irq, softirq;
    stat >> cpu >> user >> nice >> system >> idle >> iowait >> irq >> softirq;
    return user + nice + system + idle + iowait + irq + softirq;
}

double calculateCpuUsage(pid_t pid, int delay_ms) {
    long proc1 = getProcessCpuTime(pid);
    long sys1 = getTotalCpuTime();
    std::this_thread::sleep_for(std::chrono::milliseconds(delay_ms));
    long proc2 = getProcessCpuTime(pid);
    long sys2 = getTotalCpuTime();

    long proc_delta = proc2 - proc1;
    long sys_delta = sys2 - sys1;
    if (sys_delta == 0) return 0.0;

    long hz = sysconf(_SC_CLK_TCK); // get clock ticks per second
    double cpu_usage = (double(proc_delta) / sys_delta) * 100.0;
    return cpu_usage;
}

