#ifndef CROSSSLEEP_H
#define CROSSSLEEP_H

#ifdef __unix__
#include <unistd.h>
#elif defined _WIN32
#include <windows.h>
#endif  // #ifdef __unix__

void CrossSleep(int ms);

#endif  // #ifndef CROSSSLEEP_H
