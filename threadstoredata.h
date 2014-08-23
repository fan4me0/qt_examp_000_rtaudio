#ifndef THREADSTOREDATA_H
#define THREADSTOREDATA_H

// C++ Standard includes
#include <vector>

// Qt includes
#include <QtCore/qrunnable.h>

// Stk includes
// App includes

class threadStoreData : public QRunnable
{
public:
    void run();
    void setPointer( std::vector<std::vector<double>> &ptr );
    void storeData();
private:
    std::vector<std::vector<double>> m_ptr;
};

#endif // THREADSTOREDATA_H
