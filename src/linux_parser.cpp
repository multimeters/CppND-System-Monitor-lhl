#include <dirent.h>
#include <unistd.h>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>

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
  float mem_total;
  float mem_free;
  string key;
  string line;
  std::ifstream filestream(kProcDirectory+kMeminfoFilename);
  if (filestream.is_open()) {
      std::getline(filestream, line);
      std::istringstream linestream(line);
      linestream >> key >> mem_total;

      std::getline(filestream, line);
      std::istringstream  linestream2(line);
      linestream2 >> key >> mem_free;
  }
  return (mem_total-mem_free)/mem_total;
  
  
}

// TODO: Read and return the system uptime
long LinuxParser::UpTime() { 
  long uptime;
  string line;
  std::ifstream stream(kProcDirectory + kUptimeFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> uptime;
  }
  return uptime;
}

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { 
  long jiffies_=0;
  long temp_jiffies_;
  string cpu_name;
  string line;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> cpu_name;
    while(linestream)
    {
      linestream >> temp_jiffies_;
      jiffies_+=temp_jiffies_;
    }
  }
  return jiffies_; 
}

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid) { 
  string line;
  long long_value;
  long activeJiffies_=0;
  string str_value;
  std::ifstream filestream(kProcDirectory + to_string(pid)+kStatFilename);
  if (filestream.is_open()) {
      std::getline(filestream, line);
      std::istringstream linestream(line);     
      linestream >> str_value;
      linestream >> str_value;
      linestream >> str_value;
      int cnt=0;
      while (linestream >> long_value) {
        cnt++;
        if (cnt == 11) {
          activeJiffies_+=long_value;
        }
        if (cnt == 12) {
          activeJiffies_+=long_value;
        }
        if (cnt == 13) {
          activeJiffies_+=long_value;
        }
        if (cnt == 14) {
          activeJiffies_+=long_value;
          return activeJiffies_;
        }
      }
  }
  return 0; 
}

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { 

  vector<string> utilization=LinuxParser::CpuUtilization();
  vector<long> Jiffies;
 
    std::transform(utilization.begin(), utilization.end(), std::back_inserter(Jiffies),
        [&](std::string s) {
            return stoi(s);
        });
  long vActiveJiffies=Jiffies[CPUStates::kUser_]+Jiffies[CPUStates::kNice_]+Jiffies[CPUStates::kSystem_]
  +Jiffies[CPUStates::kIRQ_]+Jiffies[CPUStates::kSoftIRQ_]+Jiffies[CPUStates::kSteal_];
  return vActiveJiffies;
}

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() {
  vector<string> utilization=LinuxParser::CpuUtilization();
  vector<long> vIdleJiffies;
 
    std::transform(utilization.begin(), utilization.end(), std::back_inserter(vIdleJiffies),
        [&](std::string s) {
            return stoi(s);
        });
  long idle_jiffies_=vIdleJiffies[CPUStates::kIdle_]+vIdleJiffies[CPUStates::kIOwait_];
  return idle_jiffies_; 
}


// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { 
  vector<string> CpuUtil;
  string temp_jiffies_;
  string line;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> temp_jiffies_;//cpu string
    while(linestream)
    {
      linestream >> temp_jiffies_;
      CpuUtil.push_back(temp_jiffies_);
    }
  }
  return CpuUtil; 
}
// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() { 
  string line;
  string key;
  int value;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "processes") {
          return value;
        }
      }
    }
  }
  return 0;
}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() { 
  string line;
  string key;
  int value;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "procs_running") {
          return value;
        }
      }
    }
  }
  return 0; }

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid) { 
  string line;
  string flie_path=kProcDirectory + to_string(pid)+kCmdlineFilename;
  std::ifstream filestream(flie_path);
  if (filestream.is_open()) {
    std::getline(filestream, line);
  }
  return line; }

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid) { 
  string line;
  string key;
  float value=0.12f;
  std::ifstream filestream(kProcDirectory + to_string(pid)+kStatusFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);     
      while (linestream >> key >> value) {
        if (key == "VmSize:") {  
          std::stringstream buf;
	        buf.precision(2);//覆盖默认精度
	        buf.setf(std::ios::fixed);
          buf<<(value/1000);
          return buf.str();
        }
      }
    }
  }
  return ""; 
  return string(); }

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid) { 
  string line;
  string key;
  string value;
  std::ifstream filestream(kProcDirectory + to_string(pid)+kStatusFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);     
      while (linestream >> key >> value) {
        if (key == "Uid:") {
          return value;
        }
      }
    }
  }
  return ""; 
}

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid) { 
  string uid_=LinuxParser::Uid(pid);
  string line;
  string key;
  string value1,value2;
  std::ifstream filestream(kPasswordPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {   
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);     
      while (linestream >> key >> value1 >> value2) {
        if (value2 == uid_) {
          return key;
        }
      }
    }
  }
  return ""; 
  }

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid) { 
  string line;
  long long_value;
  //vector<long> value_;
  string str_value;
  std::ifstream filestream(kProcDirectory + to_string(pid)+kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);     
      linestream >> str_value;
      linestream >> str_value;
      linestream >> str_value;
      int cnt=0;
      while (linestream >> long_value) {
        cnt++;
        if (cnt == 19) {
          return long_value;
        }
      }
    }
  }
  return 0; }
