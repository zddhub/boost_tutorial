#include <iostream>

using namespace std;

#include <boost/thread.hpp>

void hello()
{
    cout << "Method #1" <<endl;
}

int main()
{
    cout << "boost::thread: " << endl;

    //#1: Simple method
    boost::thread th1(&hello);
    cout << "main thread " <<endl;
    th1.join();

    return 0;
}

