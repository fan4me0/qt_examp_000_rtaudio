// C++ Standard includes
#include <iterator>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

// App includes
#include "threadstoredata.h"
#include "timer.h"
#include "parameters.h"

void threadStoreData::run()
{
    storeData();
}

void threadStoreData::setPointer( std::vector<std::vector<double>> &prt )
{
    m_ptr = prt;
}

void threadStoreData::storeData()
{
    timer sw;
    std::cout << "Hello from the thread..." << std::endl;
    std::ofstream out_curve;
    out_curve.open( "signal_samples.txt", std::ios::out );
    std::stringstream   ssline;
    ssline.setf( std::ios::fixed, std::ios::floatfield );
    ssline.precision( 6 );

    for( int iter = 0; iter < ROW_NBR; iter++ )
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
