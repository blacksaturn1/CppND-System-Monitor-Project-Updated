#include <string>

#include "format.h"
#include <math.h>
#include <iomanip>

using std::string;

// TODONE: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) {
        double hours,minutes;
        long rem_seconds; 
        double fractHours = modf(seconds/3660.0,&hours);
        double fractMinutes = modf(fractHours*60.0,&minutes);
        rem_seconds= fractMinutes*60.0;
        std::stringstream ss;
        ss << std::setw(2) << std::setfill('0') << hours<<":";
        ss << std::setw(2) << std::setfill('0') << minutes<<":";
        ss << std::setw(2) << std::setfill('0') << rem_seconds;
        return ss.str(); 
    }