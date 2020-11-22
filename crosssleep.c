#include "crosssleep.h"

void CrossSleep(int ms)
{
#ifdef __unix__
    usleep(ms * 1000);
#elif defined _WIN32
    Sleep(ms);
#endif  // #ifdef __unix__
}