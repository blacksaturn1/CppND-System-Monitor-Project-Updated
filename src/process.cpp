#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>

#include "process.h"
#include "linux_parser.h"
//#include "system.h"

#include <iostream>
#include <asm/param.h>
using std::string;
using std::to_string;
using std::vector;


void Process::SetProcess(int pid,long sysTicksSecond){
        pid_=pid;

        string user=LinuxParser::User(pid);
        std::string command=LinuxParser::Command(pid);
        std::string ram=LinuxParser::Ram(pid);
        long int processTimeInSeconds=LinuxParser::UpTime(pid)/sysTicksSecond;
        float cpu = LinuxParser::ActiveJiffies(pid);
        cpu=CalculateCpu(pid,processTimeInSeconds);
        SetProcess(pid,user,command,cpu,ram,processTimeInSeconds);
        
}

void Process::SetProcess(int pid,string user ,string command,float cpu,string ram,long int uptime){
        pid_=pid;
        user_=user;
        command_=command;
        cpu_=cpu;
        ram_=(ram!="")?ram:"0";
        uptime_=uptime;
        
}

float Process::CalculateCpu(int pid,long processTimeInSeconds) { 
        const string sep="---------------";
        string logFile="."+LinuxParser::kStatFilename+std::to_string(pid)+".txt";
        //std::ofstream filestream(logFile);
      
      
        //HZ 
        long hertz_ticksPerSecond=LinuxParser::Jiffies();

        long activePidJiffies= LinuxParser::ActiveJiffies(pid);
        long sysUptime  = LinuxParser::UpTime();
       
        long secondsForProcess= sysUptime -(processTimeInSeconds);
        float cpu_Usage = 0;
        cpu_Usage =activePidJiffies/hertz_ticksPerSecond;//secondsForProcess;//(activePidJiffies/hertz_ticksPerSecond)/secondsForProcess;
        cpu_Usage = cpu_Usage/secondsForProcess*100;
      
        //filestream<<pid<<jiffies<<activePidJiffies<<cpu<<sep;
        //filestream.close();

        return cpu_Usage;
        
      
    }


// TODONE: Return this process's ID
int Process::Pid() { return pid_; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() { return cpu_; }

// TODONE: Return the command that generated this process
string Process::Command() { return command_; }

// TODONE: Return this process's memory utilization
string Process::Ram() { return ram_; }

// TODONE: Return the user (name) that generated this process
string Process::User() { return user_; }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return uptime_; }

// TODONE: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const 
{ 
    //return stol(this->ram_)<stol(a.ram_); 
    return this->cpu_<a.cpu_; 
}

// TODONE
bool Process::operator>(Process const& a) const 
{ 
    //return stol(this->ram_)>stol(a.ram_); 
    return this->cpu_>a.cpu_; 
}

// // TODONE
Process& Process::operator=(const Process& p){
    this->SetProcess(p.pid_,p.user_,p.command_,p.cpu_,p.ram_,p.uptime_);
    return *this;
}

