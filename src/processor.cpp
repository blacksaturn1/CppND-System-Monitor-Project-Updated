#include "processor.h"
#include "linux_parser.h"

#include <vector>
#include <string>
#include <iostream>
#include <unistd.h>


using std::cerr;
// TODONE: Return the aggregate CPU utilization
float Processor::Utilization() { 
        
        std::vector<std::string> cpuStats2=LinuxParser::CpuUtilization();
        double user_n,nice_n,system_n,idle_n,iowait_n,irq_n,softirq_n,steal_n,guest_n,guest_nice_n;//,guest_n,guest_nice_n;
        user_n = std::stol(cpuStats2[0]);
        nice_n = std::stol(cpuStats2[1]);
        system_n = std::stol(cpuStats2[2]);
        idle_n = std::stol(cpuStats2[3]);
        iowait_n = std::stol(cpuStats2[4]);
        irq_n = std::stol(cpuStats2[5]);
        softirq_n = std::stol(cpuStats2[6]);
        steal_n = std::stol(cpuStats2[7]);
        guest_n = std::stol(cpuStats2[8]);
        guest_nice_n= std::stol(cpuStats2[9]);

        
        double idle = idle_n + iowait_n;
        double nonIdle = user_n+nice_n+system_n+irq_n+softirq_n+steal_n+guest_n+guest_nice_n ;
        double total = idle + nonIdle;
        double totalDiff = total - previousTotal_;
        if(0==totalDiff)return 0;
        double util=( (totalDiff) - (idle-previousIdle_))/(totalDiff);
        previousTotal_=total;
        previousIdle_=idle;
        return util;
      
    }