#ifndef PROCESS_H
#define PROCESS_H

#include <string>

/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
using std::string;
class Process {
 public:
   
    void SetProcess(int pid,long sysTicksSecond); 
    int Pid();                               // TODO: See src/process.cpp
    std::string User();                      // TODO: See src/process.cpp
    std::string Command();                   // TODO: See src/process.cpp
    float CpuUtilization();                  // TODO: See src/process.cpp
    std::string Ram();                       // TODO: See src/process.cpp
    long int UpTime();                       // TODO: See src/process.cpp
    bool operator<(Process const& a) const;  // TODO: See src/process.cpp
    bool operator>(Process const& a) const;  // For sort
    Process& operator=(const Process&);     // Copy for sort
    
  // TODO: Declare any necessary private members
 private:
   void SetProcess(int pid,string user ,string command,float cpu,string ram,long int uptime);
   float CalculateCpu(int pid,long processTimeInSeconds);
   int pid_;
   std::string user_;
   std::string command_;
   float cpu_;
   std::string ram_;
   long int uptime_;
   
    
    
};

#endif