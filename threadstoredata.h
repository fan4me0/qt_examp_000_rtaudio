#ifndef THREADSTOREDATA_H
#define THREADSTOREDATA_H

#include <QThreadPool>

class threadStoreData : public QRunnable
{
public:
    void run();
    void set_pointer( std::vector<std::vector<double>> &ptr );
    void storeData();
private:
    std::vector<std::vector<double>> m_ptr;
};

#endif // THREADSTOREDATA_H
