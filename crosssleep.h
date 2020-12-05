#ifndef CROSSSLEEP_H
#define CROSSSLEEP_H

#ifdef __unix__
#include <unistd.h>
#elif defined _WIN32
#include <windows.h>
#endif  // #ifdef __unix__

static inline void CrossSleep(int ms)
{
#ifdef __unix__
    usleep(ms * 1000);
#elif defined _WIN32
    Sleep(ms);
#endif  // #ifdef __unix__
}

#endif  // #ifndef CROSSSLEEP_H
