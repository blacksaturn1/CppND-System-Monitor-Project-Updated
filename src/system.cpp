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
    processes_.clear();
    //vector<Process>* proc=&processes_; 
    //oc=new vector<Process>();
    //std::cout<<x.size()<<std::endl;
    for(auto &&i:x){
        //std::cout<<"here"<<std::endl;
        //std::cout<<x.size()<<std::endl;
        std::string user=LinuxParser::User(i);
        std::string command=LinuxParser::Command(i);
        std::string ram=LinuxParser::Ram(i);
        long int uptime=LinuxParser::UpTime(i);
        float cpu=.3;
        
        Process p(i,user,command,cpu,ram,uptime);
    
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
long int System::UpTime() { return LinuxParser::UpTime(); }