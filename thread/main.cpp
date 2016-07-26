/*
 * boost::thread tutorial
 *
 * zdd / zddhub@gmail.com
 * https://github.com/zddhub/boost_tutorial
 */

#include <iostream>
#include <boost/thread.hpp>

using std::cout;
using std::cin;
using std::endl;

//#1
void run()
{
    cout << "Method #1" <<endl;
}

//#2
boost::mutex mutex;
class Count {
    int _id;
public:
    Count(int id):_id(id) {}
    void operator ()() {
        for(int i = 0; i < 10; i++) {
            boost::mutex::scoped_lock lock(mutex);
            cout << "Count id:" << _id << " " << i <<endl;
        }
    }
};

//#3
class InnerThread {
public:
    static void run() {
        cout << "class inner thread: run and start must be static." <<endl;
    }

    static void start() {
        boost::thread thread(run);
        thread.join();
    }
};

class InnerThread2 {
public:
    void run() {
        cout << "class inner thread: use boost::bind" <<endl;
    }

    void start() {
        boost::function0<void> f = boost::bind(&InnerThread2::run, this);
        boost::thread thread(f);
        thread.join();
    }
};

//#4
class SingletonThread {
public:
    void run() {
        cout << "Singleton thread" <<endl;
    }

    void start() {
        boost::function0<void> f = boost::bind(&SingletonThread::run, SingletonThread::getInstance());
        boost::thread thread(f);
        thread.join();
    }

    static SingletonThread* getInstance() {
        if(!_instance) {
            _instance = new SingletonThread;
        }
        return _instance;
    }
private:
    SingletonThread() {}
    static SingletonThread* _instance;
};
SingletonThread* SingletonThread::_instance = 0;

//#5
class Class {
public:
    void run(const std::string& str) {
        cout <<str <<endl;
    }

    int add(int x, int y) {
        cout << "x+y=" <<x+y<<endl;
        return x+y;
    }
};

//#6
int add(int x, int y) {
    return x+y;
}

int main()
{
    cout << "boost::thread: " << endl;

    //#1: Simple method
    boost::thread th1(&run);
    cout << "main thread " <<endl;
    th1.join();

    //#2: Through class operator() method
    boost::thread th21(Count(1));
    boost::thread th22(Count(2));
    th21.join();
    th22.join();

    //#3: Class inner thread : static method
    InnerThread ith;
    ith.start();
    InnerThread::start();

    InnerThread2 ith2;
    ith2.start();

    //#4: Singleton thread
    SingletonThread *st = SingletonThread::getInstance();
    st->start();

    //#5: Outer class thread
    Class cls;
    boost::thread outer_thread(boost::bind(&Class::run, &cls, "Outer thread"));
    outer_thread.join();

    //#6: Complex method: with return value
    boost::function2<int, int, int> f = &add;
    boost::packaged_task<int> pt(boost::bind<int>(f, 1, 2));
    boost::unique_future<int> fi = pt.get_future();
    boost::thread th2(boost::move(pt));
    fi.wait();
    th2.join();
    cout <<"x+y="<<fi.get()<<endl;

   // boost::packaged_task<int> pt_cls(boost::bind<int>(&Class::add, &cls, 1, 2));
   // boost::unique_future<int> fi_cls = pt_cls.get_future();
   // boost::thread th2_cls(boost::move(pt_cls));
   // fi_cls.wait();
   // th2_cls.join();
   // cout <<"x+y="<<fi_cls.get()<<endl;

    /*
     *related functions
     *  boost::thread
     *  boost::function
     *  boost::bind
     */

    //some usages:
    int x = 1, y =2;
    cout << "x+y=" <<boost::bind<int>(f, _1, _2)(x,y)<<endl;


    return 0;
}

