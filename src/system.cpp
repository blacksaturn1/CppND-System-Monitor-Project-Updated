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
Processor& System::Cpu() { return cpu_; }

// TODO: Return a container composed of the system's processes
vector<Process>& System::Processes() { 
    vector<int> x=LinuxParser::Pids();
    //vector<Process>* proc=&processes_; 
    //oc=new vector<Process>();
    
    for(auto &&i:x){
        //std::cout<<"here"<<std::endl;

        std::string user=LinuxParser::User(i);
        std::string command=LinuxParser::Command(i);
        float cpu=.3;
        std::string ram="100";
        long int uptime=10;;
        Process p(i,user,command,cpu,ram,uptime);
    
        processes_.push_back(p);

    }
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
long int System::UpTime() { return LinuxParser::UpTime(); }