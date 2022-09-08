#ifndef PROCESS_H
#define PROCESS_H

#include <string>
using std::string;
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  int Pid();                               // TODO: See src/process.cpp
  std::string User();                      // TODO: See src/process.cpp
  std::string Command();                   // TODO: See src/process.cpp
  float CpuUtilization();                  // TODO: See src/process.cpp
  std::string Ram();                       // TODO: See src/process.cpp
  long int UpTime();                       // TODO: See src/process.cpp
  bool operator<(Process const& a) const;  // TODO: See src/process.cpp
  
  void setPid(int p){Pid_=p;}
  void setUser(string u){User_=u;}
  void setCpu(float c){cpu_=c;}
  void setRam(string r){Ram_=r;}
  void setUptime(long u){UpTime_=u;}
  void setCommand(string c){Command_=c;}
  // TODO: Declare any necessary private members
 private:
  int Pid_;
  string User_;
  float cpu_;
  string Ram_;
  long UpTime_;
  string Command_;
};

#endif