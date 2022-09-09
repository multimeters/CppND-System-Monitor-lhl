#include "system.h"

#include <unistd.h>

#include <cstddef>
#include <set>
#include <string>
#include <vector>

#include "format.h"
#include "linux_parser.h"
#include "process.h"
#include "processor.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;
/*You need to complete the mentioned TODOs in order to satisfy the rubric
criteria "The student will be able to extract and display basic data about the
system."

You need to properly format the uptime. Refer to the comments mentioned in
format. cpp for formatting the uptime.*/

// TODO: Return the system's CPU
Processor& System::Cpu() {
  float total = LinuxParser::Jiffies();
  float idle = LinuxParser::IdleJiffies();
  float cpu_util = (total - idle) / total;
  cpu_.setUtil(cpu_util);
  return cpu_;
}

// TODO: Return a container composed of the system's processes
vector<Process>& System::Processes() {
  int procs_count = LinuxParser::Pids().size();
  // vector<Process> sprocesses_;
  Process temp_processes_;
  processes_.clear();
  for (int i = 0; i <= (procs_count - 1); i++) {
    int pid = LinuxParser::Pids()[i];
    string command_ = LinuxParser::Command(pid);
    temp_processes_.setPid(pid);

    long process_total_time = LinuxParser::ActiveJiffies(pid);
    long starttime = LinuxParser::UpTime(pid);
    int Hertz = 100;  // getconf CLK_TCK
    long seconds = LinuxParser::UpTime() - (starttime / Hertz);
    float cpu_util;
    if (seconds != 0) {
      cpu_util = (((float)process_total_time / (float)Hertz) / (float)seconds);
    } else {
      cpu_util = 0;
    }
    temp_processes_.setCpu(cpu_util);
    temp_processes_.setCommand(command_);
    temp_processes_.setRam(LinuxParser::Ram(pid));
    temp_processes_.setUptime(LinuxParser::UpTime(pid) / Hertz);
    temp_processes_.setUser(LinuxParser::User(pid));
    processes_.push_back(temp_processes_);
  }
  sort(processes_.begin(), processes_.end());
  reverse(processes_.begin(), processes_.end());
  return processes_;
  // return processes_;
}

// TODO: Return the system's kernel identifier (string)
std::string System::Kernel() {
  return LinuxParser::Kernel();
  ;
}

// TODO: Return the system's memory utilization
float System::MemoryUtilization() { return LinuxParser::MemoryUtilization(); }

// TODO: Return the operating system name
std::string System::OperatingSystem() { return LinuxParser::OperatingSystem(); }

// TODO: Return the number of processes actively running on the system
int System::RunningProcesses() { return LinuxParser::RunningProcesses(); }

// TODO: Return the total number of processes on the system
int System::TotalProcesses() { return LinuxParser::TotalProcesses(); }

// TODO: Return the number of seconds since the system started running
long int System::UpTime() { return LinuxParser::UpTime(); }
