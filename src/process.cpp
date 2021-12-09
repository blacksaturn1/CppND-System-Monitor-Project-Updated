#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>

#include "process.h"
#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;
Process::Process(int pid,string user ,string command,float cpu,string ram,int uptime){
    pid_=pid;
    user_=user;
    command_=command;
    cpu_=cpu;
    ram_=ram;
    uptime_=uptime;
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
    //std::cout<<"HERERE"<<std::endl;
    return stol(this->ram_)<stol(a.ram_); 
}

// TODONE
bool Process::operator>(Process const& a) const 
{ 
    return stol(this->ram_)>stol(a.ram_); 
}