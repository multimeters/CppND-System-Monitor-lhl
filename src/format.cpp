#include <string>

#include "format.h"

using std::string;
using std::to_string;
// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) { 
    // cal hours
	int calhours = seconds / 60 / 60; 
	// cal monutes
	int calminutes = (seconds-calhours*3600) / 60;
	// cal secondes
	int calseconds = (seconds-calhours*3600) % 60;
	// format
    string t;
    if(calhours<10)
    {t+="0";}
    t+=to_string(calhours);
    t+=":";
    if(calminutes<10)
    {t=t+"0";}
    t=t+to_string(calminutes);
    t+=":";
    if(calseconds<10)
    {t=t+"0";}
    t=t+to_string(calseconds);

    return t; 
    }