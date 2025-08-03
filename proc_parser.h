#pragma once
#include <string>
#include <vector>

struct ProcessInfo {
    std::string pid;
    float cpu;
    std::string memory;
    std::string command;
};

std::vector<ProcessInfo> getActiveProcesses();
