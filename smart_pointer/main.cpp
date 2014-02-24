#include <string>
#include <iostream>
using namespace std;

#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

class Object {
public:
    Object() {
        cout << "Object constructor" <<endl;
    }

    ~Object() {
        cout << "Object destroy" <<endl;
    }

    void do_something() {
        cout << "do something ... " <<endl;
    }
};

int main()
{
    cout << "smart pointer:"
            "\n\t(boost::weak_ptr, boost::shared_ptr, boost::scoped_ptr)" << endl;
    /*
     * Boost智能指针: 使用引用计数器实现
     */

    //#: scoped_ptr: 在离开作用域后对象会被自动释放
    //  scoped_ptr使用的限制：
    //    1、不能转换所有权，不能作为函数返回值
    //    2、不能共享所有权，不能用于stl容器
    //    3、不能管理数组
    {
        boost::scoped_ptr<Object> s_ptr(new Object());
        s_ptr->do_something();
    }

    //#: shared_ptr: (强引用)可以共享所有权
    /*
     * boost::shared_ptr的使用规则：
     * 1、避免对shared_ptr所管理的对象直接了进行内存管理操作
     * 2、不能自动管理循环引用
     * 3、不要构造一个临时的shared_ptr作为函数的参数
     *    如：错误的用法: fun(boost:;shared_ptr<Object>(new Object()), g());
     *    正确的用法如下：
     *     boost:;shared_ptr<Object> sp(new Object());
     *     fun(sp, g());
     */
    boost::shared_ptr<Object> sp1(new Object());
    cout << "Ref count: " << sp1.use_count() <<endl;

    boost::shared_ptr<Object> sp2 = sp1;
    cout << "Ref count: " << sp2.use_count() <<endl;

    sp1.reset();
    cout << "Ref count: " << sp1.use_count() <<endl;
    cout << "Ref count: " << sp2.use_count() <<endl;

    sp2.reset();
    cout << "Ref count: " << sp1.use_count() <<endl;
    cout << "Ref count: " << sp2.use_count() <<endl;

    //#: weak_ptr: (弱引用) 不改变计数器
    boost::shared_ptr<Object> sp(new Object());
    boost::weak_ptr<Object> wp(sp);
    cout << "Ref count: " << sp.use_count() <<endl;
    cout << "Ref count: " << wp.use_count() <<endl;
    return 0;
}

