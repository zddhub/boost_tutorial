/*
 * boost::property_tree tutorial
 *
 * zdd / zddhub@gmail.com
 * https://github.com/zddhub/boost_tutorial
 */

#include <iostream>
#include <vector>
using namespace std;

#include <boost/any.hpp>

class Customer {
public:
    Customer(const std::string& name) : _name(name) {}
    std::string toString() {
        return _name;
    }
private:
    std::string _name;
};

int main()
{
    cout << "boost::any: " << endl;

    //boost::any可以存放任意类型的对象
    typedef std::vector<boost::any> vector_any;
    vector_any va;

    va.push_back(100); //存放常数
    va.push_back(std::string("zddhub.com")); //存放string，注意vector_any.push_back("zddhub.com")会被当成字符数组
    va.push_back(new Customer("zdd"));//自定义类型
    va.push_back(Customer("zddhub"));

    //根据类型进行显示
    for(vector_any::iterator it = va.begin(); it != va.end(); ++it) {
        if(it->type() == typeid(int)) {
            cout << "int: " << boost::any_cast<int>(*it)<<endl;
        } else if(it->type() == typeid(std::string)) {
            cout << "string: " << boost::any_cast<std::string>(*it).c_str() <<endl;
        } else if(it->type() == typeid(Customer*)) {
            Customer *c = boost::any_cast<Customer*>(*it);
            cout << "Custormer* : " << c->toString().c_str()<<endl;
            delete c;
        } else if(it->type() == typeid(Customer)) {
            cout << "Custormer : " << boost::any_cast<Customer>(*it).toString().c_str()<<endl;
        }
    }

    return 0;
}

