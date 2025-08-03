#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <dirent.h>
#include <unistd.h>
#include <cstring>
#include "CpuMonitor.h"

std::string getCommand(pid_t pid) {
    std::ifstream cmdline("/proc/" + std::to_string(pid) + "/cmdline");
    std::string cmd;
    std::getline(cmdline, cmd);
    return cmd.empty() ? "-" : cmd;
}

std::string getMemoryUsage(pid_t pid) {
    std::ifstream status("/proc/" + std::to_string(pid) + "/status");
    std::string line;
    while (std::getline(status, line)) {
        if (line.find("VmRSS:") == 0) {
            std::istringstream iss(line);
            std::string key;
            int memKb;
            std::string unit;
            iss >> key >> memKb >> unit;
            return std::to_string(memKb / 1024) + " MB";
        }
    }
    return "N/A";
}

int main() {
    std::cout << "PID\tCPU%\tMemory\tCMD\n";
    DIR* proc = opendir("/proc");
    struct dirent* entry;

    while ((entry = readdir(proc)) != nullptr) {
        if (!isdigit(entry->d_name[0])) continue;
        pid_t pid = atoi(entry->d_name);
        double cpu = calculateCpuUsage(pid, 100);
        std::string mem = getMemoryUsage(pid);
        std::string cmd = getCommand(pid);

        std::cout << pid << "\t" << int(cpu) << "%\t" << mem << "\t" << cmd << "\n";
    }

    closedir(proc);
    return 0;
}
