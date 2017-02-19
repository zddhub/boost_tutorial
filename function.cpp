#include <iostream>
#include <string>
using namespace std;

#include <boost/function.hpp>
#include <boost/bind.hpp>

typedef boost::function<void (int, int, const std::string&)> Callback;

void test(int n, Callback callback = Callback()) {
    for(int i = 0; i < n; i++) {
        //cout << "i*i = " << i*i <<endl;

        if(callback)
            callback(i, n, "");
    }
}

void print(int index, int total, const std::string& info) {
    if(index +1 != total)
        cout << info.c_str() << index+1 << "/" << total <<"\r"<<std::flush;
    else
        cout << info.c_str() << index+1 << "/" << total <<"."<<std::endl;
}

int main()
{
    cout << "Boost::function callbank_fun" << endl;

    test(1000, print);

    test(1000, boost::bind(&print, _1, _2, "compute i*i "));

    return 0;
}

