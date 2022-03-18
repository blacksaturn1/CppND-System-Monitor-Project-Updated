#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>

#include <iostream>
#include <algorithm>

#include <charconv>

#include "process.h"
#include "processor.h"
#include "system.h"
#include "linux_parser.h"
using std::set;
using std::size_t;
using std::string;
using std::vector;

System::System():hertz_(LinuxParser::Jiffies()){}

long System::Hertz() const{ return hertz_; }
  
// TODO: Return the system's CPU
Processor& System::Cpu() { return cpu_; }

// TODO: Return a container composed of the system's processes
vector<Process>& System::Processes() { 
    vector<int> x=LinuxParser::Pids();
    processes_.clear();
    for(auto &&i:x){
       
        Process p;
        p.SetProcess(i,Hertz());
        processes_.push_back(p);

    }
    
    std::sort(processes_.begin(), processes_.end(),std::greater<Process>());
    return processes_; 
}


// TODONE: Return the system's kernel identifier (string)
std::string System::Kernel() { return LinuxParser::Kernel(); }

// TODONE: Return the system's memory utilization
float System::MemoryUtilization() { 
     return LinuxParser::MemoryUtilization();
}

// TODONE: Return the operating system name
std::string System::OperatingSystem() { return LinuxParser::OperatingSystem(); }

// TODONE: Return the number of processes actively running on the system
int System::RunningProcesses() { return LinuxParser::RunningProcesses(); }

// TODONE: Return the total number of processes on the system
int System::TotalProcesses() { return LinuxParser::TotalProcesses(); }

// TODONE: Return the number of seconds since the system started running
long int System::UpTime() { 
    systemUptime_=LinuxParser::UpTime(); 
    return systemUptime_;
}