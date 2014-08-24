#ifndef TIMER_H
#define TIMER_H

// C++ Standard includes
#include <ctime>
#include <string>

class timer
{
public:
    timer() : m_start( std::clock() )
    {
        //start counting time
    }

    timer( const std::string eventName = "" ) : m_event_name( eventName ),
                                                m_start( std::clock() )
    {
        //start counting time
    }

    ~timer()
    {
        clock_t total = clock()- m_start; //get elapsed time
        std::cout << "==start== Time duration for event: " << m_event_name << " =========" << std::endl;
        std::cout << "total of ticks for this activity: " << total << std::endl;
        std::cout << "in seconds: "<< double(total)/CLOCKS_PER_SEC << std::endl;
        std::cout << "==end==== Time duration for event: " << m_event_name << " =========" << std::endl;
    }

private:
    const std::string m_event_name;
    std::clock_t m_start;
};

#endif // TIMER_H
