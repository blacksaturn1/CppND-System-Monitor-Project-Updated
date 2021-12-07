#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>

#include <iostream>

#include "linux_parser.h"

using std::cerr;
using std::stof;
using std::string;
using std::to_string;
using std::vector;

// TODONE: An example of how to read data from the filesystem
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

// TODONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, version, kernel;
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

// TODONE: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() {
  string key, value;
  float total, free;
  string line;
  std::ifstream filestream(kProcDirectory + kMeminfoFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "MemTotal:") {
          total = stof(value);
        }
        if (key == "MemFree:") {
          free = stof(value);
        }
      }
    }
  }
  return (total-free)/total;
}

// TODONE: Read and return the system uptime
long LinuxParser::UpTime() { 
  string key, value;
  long seconds;
  string line;
  std::ifstream filestream(kProcDirectory + kUptimeFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      linestream>>value;
      //cerr<<value;
      seconds = std::stof(value);
      

    }
  }
  return seconds; 
 }

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) { return 0; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

// TODONE: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { 
    string value;
    string line;
    vector<string> cpuData;
    std::ifstream filestream(kProcDirectory + kStatFilename);
    if (filestream.is_open()) {
      while (std::getline(filestream, line)) {
        std::istringstream linestream(line);
      linestream>>value;
      int x=8;
        while(x--){
          linestream>>value;
          cpuData.push_back(value);
        }
      }
    }
    return cpuData; 
}

// TODONE: Read and return the total number of processes
int LinuxParser::TotalProcesses() { 
    string key, value;
    long total;
    string line;
    std::ifstream filestream(kProcDirectory + kStatFilename);
    if (filestream.is_open()) {
      while (std::getline(filestream, line)) {
        std::istringstream linestream(line);
      linestream>>key>>value;
      if(key=="procs_running"){
        total = std::stol(value);
      }

    }
  }
  return total; 
  }

// TODONE: Read and return the number of running processes
int LinuxParser::RunningProcesses() { 
  string key, value;
  long running;
  string line;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      linestream>>key>>value;
      if(key=="processes"){
        running = std::stol(value);
      }

    }
  }
  return running; 
  }

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid)  {
  string command;
  string key, value;
  string line;
  std::ifstream filestream(kProcDirectory+to_string(pid) + kCmdlineFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), '\0', ' ');
      std::istringstream linestream(line);
      while(linestream>>value){
        command+=value;
      }
      
    }
  }

   return command; 
}

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid) {
  string uid;
  string key, value;
  string line;
  std::ifstream filestream(kProcDirectory+to_string(pid) + kStatusFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      linestream>>key>>value;
      if(key=="Uid:"){
        uid = value;
      }

    }
  }
   return uid; 
   
}

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid) { 
  string uid=LinuxParser::Uid(pid);
  string user=uid;
  string line;
  string key,x, value;
  std::ifstream filestream(kPasswordPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      linestream>>value>>x>>key;
      if(key==uid){
        user = value;
      }

    }
  }

  return user;
}


// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid[[maybe_unused]]) { return 0; }
