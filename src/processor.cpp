#include "processor.h"
#include "linux_parser.h"
#include <chrono>
#include <thread>

using namespace std::chrono;
using namespace std::this_thread;

// TODO: Return the aggregate CPU utilization
double Processor::Utilization() {
    std::vector<long> cpuUtil = convertToFloat();
    
    float prevIdle = cpuUtil[3] + cpuUtil[4];
    float prevNodeIdel = cpuUtil[0] + cpuUtil[1] + cpuUtil[2] + cpuUtil[5] + cpuUtil[6] + cpuUtil[7];
    float prevTotal = prevIdle + prevNodeIdel;

    sleep_for(milliseconds(500));

    std::vector<long> cpuUtilNow = convertToFloat();

    float idle = cpuUtilNow[3] + cpuUtilNow[4];
    float nodeIdel = cpuUtilNow[0] + cpuUtilNow[1] + cpuUtilNow[2] + cpuUtilNow[5] + cpuUtilNow[6] + cpuUtilNow[7];
    float total = idle + nodeIdel;

    total = total - prevTotal;
    idle = idle - prevIdle;

    
    return (total - idle)/total; 
}

std::vector<long> Processor::convertToFloat() {
    std::vector<long> cpuUtilDoubles;
    const std::vector<std::string> cpuStrings = LinuxParser::CpuUtilization();
    for (u_int it = 0; it < cpuStrings.size(); it++) {
        try {
            cpuUtilDoubles.push_back(std::stol(cpuStrings[it]));
        } catch (const std::invalid_argument& arg) {
            cpuUtilDoubles.push_back((long)0);
        }
    }
    return cpuUtilDoubles;
}