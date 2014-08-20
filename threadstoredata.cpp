// C++ Standard includes
#include <iterator>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

#include "threadstoredata.h"
#include <QThreadPool>

//threadStoreData::threadStoreData()
//{
//}
const int row_nbr = 200;

#include <ctime>

class stopwatch
{
public:
    stopwatch() : start(std::clock())
    {} //start counting time

    ~stopwatch()
    {
        clock_t total = clock()-start; //get elapsed time
        std::cout << "total of ticks for this activity: " << total << std::endl;
        std::cout << "in seconds: "<< double(total)/CLOCKS_PER_SEC << std::endl;
    }

private:
    std::clock_t start;
};

void threadStoreData::run()
{
    stopwatch sw;
    std::cout << "Hello from the thread..." << std::endl;
    std::ofstream out_curve;
    out_curve.open( "signal_samples.txt", std::ios::out );
    std::stringstream   ssline;
    ssline.setf( std::ios::fixed, std::ios::floatfield );
    ssline.precision( 6 );

    for( int iter = 0; iter < row_nbr; iter++ )
    {
        for( auto & index: m_ptr[ iter ] )
        {
            //std::cout << index << std::endl;
            ssline << index;
            out_curve << ssline.str() << "\n";
            ssline.str( "" ) ;
        }
    }
    out_curve.close();
    std::cout << "Finished storing data ..." << std::endl;
}

void threadStoreData::set_pointer( std::vector<std::vector<double>> &prt )
{
    m_ptr = prt;
}

void threadStoreData::storeData()
{

}
