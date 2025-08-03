#include "proc_parser.h"
#include <dirent.h>
#include <fstream>
#include <algorithm>


std::vector<ProcessInfo> getActiveProcesses() {
    std::vector<ProcessInfo> processes;

    DIR* dir = opendir("/proc");
    struct dirent* entry;

    while ((entry = readdir(dir)) != nullptr) {
        std::string pid = entry->d_name;
        if (std::all_of(pid.begin(), pid.end(), ::isdigit)) {
            std::ifstream cmdline("/proc/" + pid + "/cmdline");
            std::string cmd;
            std::getline(cmdline, cmd);

            ProcessInfo p;
            p.pid = pid;
            p.command = cmd.empty() ? "-" : cmd;
            p.cpu = 0.0f; // Placeholder
            p.memory = "N/A"; // Placeholder
            processes.push_back(p);
        }
    }

    closedir(dir);
    return processes;
}
