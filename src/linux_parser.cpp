#include <dirent.h>
#include <unistd.h>
#include <sstream>
#include <string>
#include <vector>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, kernel, version;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() {
  float totalMemory, freeMemory;
  float mem;
  string line, key, value, type;
  std::ifstream file(kProcDirectory + kMeminfoFilename);
  if(file.is_open()){
    while(std::getline(file, line)){
      std::istringstream linestream(line);
      linestream >> key >> value >> type;
      if(key == "MemTotal:"){
        std::stringstream v(value);
        v >> totalMemory;
      }
      else if (key == "MemFree:")
      {
        std::stringstream v(value);
        v >> freeMemory;
      }
    }
    mem = ((totalMemory - freeMemory)/totalMemory);
  }
  return mem; 
}

// TODO: Read and return the system uptime
long LinuxParser::UpTime() { 
  int upTime;
  string line;
  std::ifstream file(kProcDirectory + kUptimeFilename);
  if(file.is_open()){
    while(std::getline(file, line)){
      std::istringstream linestream(line);
      linestream >> upTime;
    }
  }
  return upTime; 
  
}

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { 
  string line, key, value;
  std::ifstream file(kProcDirectory + kStatFilename);
  long jiff;
  if (file.is_open()){
    while(std::getline(file, line)){
      std::stringstream linestream(line);
      linestream >> key >> value;
      if (key == "cpu"){
        std::istringstream v(value);
        v >> jiff;
        break;
      }
    }
  }
  return jiff; 
}

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) { 
  return 0;
}

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { 
  vector<string> cpuValues{};
  string line;
  string key;
  string vuser, vnice, vsystem, vidle, viowait, virq, vsoftirq, vsteal, vguest,
      vguest_nice;
  std::ifstream file(kProcDirectory + kStatFilename);
  if (file.is_open()) {
    while (std::getline(file, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> vuser >> vnice >> vsystem >> vidle >>
             viowait >> virq >> vsoftirq >> vsteal >> vguest >> vguest_nice) {
        if (key == "cpu") {
          cpuValues.push_back(vuser);
          cpuValues.push_back(vnice);
          cpuValues.push_back(vsystem);
          cpuValues.push_back(vidle);
          cpuValues.push_back(viowait);
          cpuValues.push_back(virq);
          cpuValues.push_back(vsoftirq);
          cpuValues.push_back(vsteal);
          cpuValues.push_back(vguest);
          cpuValues.push_back(vguest_nice);
          break;
        }
      }
    }
  }
  return cpuValues; 
}

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() { 
  string line, key, value;
  int total;
  std::ifstream file(kProcDirectory + kStatFilename);
  if (file.is_open()){
    while (std::getline(file, line))
    {
      std::stringstream linestream(line);
      linestream >> key >> value;
      if (key == "processes"){
        total = std::stoi(value);
        break;
      }
    }
    
  } 
  return total;
}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() { 
  string line, key, value;
  int total;
  std::ifstream file(kProcDirectory + kStatFilename);
  if (file.is_open()){
    while (std::getline(file, line))
    {
      std::stringstream linestream(line);
      linestream >> key >> value;
      if (key == "procs_running"){
        total = std::stoi(value);
        break;
      }
    }
    
  } 
  return total;
}

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid) { 
  string line, value;
  std::ifstream file(kProcDirectory + std::to_string(pid) + kCmdlineFilename);
  if (file.is_open()){
    while(std::getline(file, line)){
      std::stringstream linestream(line);
      linestream >> value;
    }
  }
  return value;
}

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid) { 
  string line, key, value, type;
  std::ifstream file(kProcDirectory + "/" + std::to_string(pid) + kStatusFilename);
  if(file.is_open()){
    while(std::getline(file, line)){
      std::istringstream linestream(line);
      linestream >> key >> value >> type;
      if(key == "VmSize:"){
        return value;
      }
    }
  }
  return "10"; 
}

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid) { 
  string line, key, value;
  std::ifstream file (kProcDirectory + "/" + std::to_string(pid) + kStatusFilename);
  if(file.is_open()){
    while(std::getline(file, line)){
      std::stringstream linestream(line);
      linestream >> key >> value;
      if(key == "Uid:"){
        return value;
      }
    }
  }
  return value;
}

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid) { 

  string line, user, x ,id;
  string uid = Uid(pid);

  std::ifstream file("/etc/passwd");
  if (file.is_open()){
    while (std::getline(file, line))
    {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::stringstream linestream (line);
      linestream >> user >> x >> id;
      if(id == uid){
        return user;
      }
    }
    
  }
  
  return user; 
}

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid) { 

  string line, value;
  long uptime;
  std::ifstream file(kProcDirectory + "/" + std::to_string(pid) + kStatFilename);
  if (file.is_open()) {
    while (std::getline(file, line)) {
      std::istringstream linestream(line);
      for (int c = 1 ; c <= 24 ; c++){
        linestream >> value;
        if (c == 22){
          uptime = std::stol(value) / sysconf(_SC_CLK_TCK);
        }
      }
    }
  }
  return uptime;
}

vector<float> LinuxParser::CpuUtilization(int pid){
  string line, value;
  vector<float> cpu;
  std::ifstream file(kProcDirectory + "/" + std::to_string(pid) + kStatFilename);
  if (file.is_open()) {
    while (std::getline(file, line)) {
      std::istringstream linestream(line);
      for (int c = 1 ; c <= 24 ; c++){
        linestream >> value;
        if ((c > 13 && c < 18) || c == 22){
          cpu.push_back(std::stof(value) / sysconf(_SC_CLK_TCK));
        }
      }
    }
  }
  return cpu;

}
