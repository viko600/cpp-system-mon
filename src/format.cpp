#include <string>

#include "format.h"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) { 
    int h, m, s;
    m = seconds / 60;
    h = m / 60;
    s = seconds % 60;
    string sec = s > 9 ? std::to_string(s) : "0"+std::to_string(s);
    string min = m > 9 ? std::to_string(m % 60) : "0"+std::to_string(m % 60);
    string hou = h > 9 ? std::to_string(h) : "0"+std::to_string(h);
    return hou+":"+min+":"+sec;     
}