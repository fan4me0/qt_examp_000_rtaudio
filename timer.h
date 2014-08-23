#ifndef TIMER_H
#define TIMER_H

// C++ Standard includes
#include <ctime>

class timer
{
public:
    timer() : start(std::clock())
    {} //start counting time

    ~timer()
    {
        clock_t total = clock()-start; //get elapsed time
        std::cout << "total of ticks for this activity: " << total << std::endl;
        std::cout << "in seconds: "<< double(total)/CLOCKS_PER_SEC << std::endl;
    }

private:
    std::clock_t start;
};

#endif // TIMER_H
