cmake_minimum_required(VERSION 3.23)
project(ProcMonitor)

set(CMAKE_CXX_STANDARD 14)

add_executable(ProcMonitor main.cpp proc_parser.cpp proc_parser.h CpuMonitor.cpp CpuMonitor.h)
