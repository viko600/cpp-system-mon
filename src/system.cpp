#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>
#include <iostream>

#include "process.h"
#include "processor.h"
#include "system.h"
#include "linux_parser.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;

// TODO: Return the system's CPU
Processor& System::Cpu() {
    return cpu_; 
}

// TODO: Return a container composed of the system's processes
vector<Process>& System::Processes() { 
    vector<int> procs = LinuxParser::Pids();

    vector<Process> procById{};
    
    for(int pid : procs){
        Process process(pid);
        // This will check if the process has a comand, ram and valid user
        if ((process.Command().size() != 0) && (process.User().size() != 0) && (process.Ram().size() != 0)){
            procById.emplace_back(process);
        }
    }

    // Filter the proccesses so that only the once with high CPU util are visible
    std::sort(procById.begin(), procById.end(),
        [](Process& pa, Process& pb) {
            return (pb.CpuUtilization() < pa.CpuUtilization());
        });
    // update list of processes
    processes_ = procById;

    return processes_; 
}

// TODO: Return the system's kernel identifier (string)
std::string System::Kernel() { 
    return LinuxParser::Kernel();
}

// TODO: Return the system's memory utilization
float System::MemoryUtilization() { 
    return LinuxParser::MemoryUtilization(); 
}

// TODO: Return the operating system name
std::string System::OperatingSystem() { 
    return LinuxParser::OperatingSystem(); 
}

// TODO: Return the number of processes actively running on the system
int System::RunningProcesses() { 
    return LinuxParser::RunningProcesses(); 
}

// TODO: Return the total number of processes on the system
int System::TotalProcesses() { 
    return LinuxParser::TotalProcesses(); 
}

// TODO: Return the number of seconds since the system started running
long int System::UpTime() { 
    return LinuxParser::UpTime();
}