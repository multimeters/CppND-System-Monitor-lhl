#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"
#include <sstream> 
using std::string;
using std::to_string;
using std::vector;

// TODO: Return this process's ID
int Process::Pid() { return Pid_; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() { return cpu_; }

// TODO: Return the command that generated this process
string Process::Command() { return Command_; }

// TODO: Return this process's memory utilization
string Process::Ram() { return Ram_; }

// TODO: Return the user (name) that generated this process
string Process::User() { return User_; }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return UpTime_; }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const { 
    //compare by cpu utils
    if(cpu_<a.cpu_){return true;}
    else{return false;}

    // compare by ram
    
    //float lnum;
    // if(Ram_!="")
    // {
    //     std::istringstream liss(Ram_);
    //     liss >> lnum;
    // }
    // else{lnum=0;}
    // string str=a.Ram_;
    // float rnum;
    // if(str!=""){
    //     std::istringstream riss(str);
    //     riss >> rnum;
    // }
    // else{rnum=0;}
    
    // if(lnum<rnum) {return true;}
    // else{return  false;}     
}