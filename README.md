# Linux Process Monitor (C++)

Simple CLI tool to parse active processes from /proc and display basic information.

## Features
- Lists PID and command name
- Base structure to add CPU/memory tracking
- Built with system-level file access

## Compile
```bash
g++ main.cpp proc_parser.cpp -o monitor
