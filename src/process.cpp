#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"
#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;

Process::Process(int id) {
    // Not sure if `if` statements hsould be added to validate the Ram and the CPU
    pid_ = id;
    command_ = LinuxParser::Command(pid_);
    user_ = LinuxParser::User(pid_);
}

// TODO: Return this process's ID
int Process::Pid() { 
    return pid_; 
}

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() { 
    vector<float> cpu = LinuxParser::CpuUtilization(pid_);
    long start = LinuxParser::UpTime();

    float total = cpu[0] + cpu[1] + cpu[2] + cpu[3];
    float time = start - cpu[4];

    return total/time;
    
}

// TODO: Return the command that generated this process
string Process::Command() { 
    return command_; 
}

// TODO: Return this process's memory utilization
string Process::Ram() { 
    string memKb = LinuxParser::Ram(pid_);
    long mem = std::stol(memKb);
    return std::to_string(mem/1000);
}

// TODO: Return the user (name) that generated this process
string Process::User() { return user_; }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return LinuxParser::UpTime(pid_); }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a[[maybe_unused]]) const { return true; }