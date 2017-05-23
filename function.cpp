/*
 *  EX1 : simple callback function
 *  EX2 : callback function with different types
 */

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include <boost/function.hpp>
#include <boost/bind.hpp>


// EX1
typedef boost::function<void (int, int, const std::string&)> Callback;

void test(int n, Callback callback = Callback()) {
    for(int i = 0; i < n; i++) {
        if(callback)
            callback(i, n, "");
    }
}

// EX1
void print(int index, int total, const std::string& info) {
    if(index +1 != total)
        std::cout << info.c_str() << index+1 << "/" << total <<"\r"<< std::flush;
    else
        std::cout << info.c_str() << index+1 << "/" << total <<"."<< std::endl;
}

// EX2
void print_new_value(int i) {
  std::cout << "New value is : " << i << std::endl;
}

// EX2
void interested_in_the_change(int i) {
  std::cout << "The value has been changed..." << std::endl;
}

// EX2
class Notifier {
public:
  // a template function to add observer to watch changes 
  template <typename T> void add_observer(T t) { function_vector.push_back(function_type(t)); }

  // call every observer to notify
  void change_value(int i) {
    value_ = i;
    
    for (std::size_t i = 0;i < function_vector.size();++i) {
      function_vector[i](value_);
    }
  }

private:
  typedef boost::function<void(int)> function_type;

  // a vector to save observer functions
  std::vector<function_type> function_vector; 
  int value_;

};
// EX2
class knows_the_previous_value 
{
public:
  void operator()(int i) {
    static bool first_time = true;

    if (first_time) {
      last_value_ = i;
      std::cout << "This is the first change, so I don't know the previous one." << std::endl;
      first_time = false;
      return;
    }

    std::cout << "Previous value was " << last_value_ << std::endl;
    last_value_ = i;
  }
private:
  int last_value_;
};


int main(){

    std::cout << "Boost::function callbank_fun" << std::endl;
    std::cout << "Example 1: " << std::endl;

    test(1000, print);
    test(1000, boost::bind(&print, _1, _2, "compute i*i "));

    std::cout << "--------------------------" << std::endl;
    std::cout << "Example 2: " << std::endl;

    Notifier n;

    // add three observers
    n.add_observer(&print_new_value);           // function pointer
    n.add_observer(&interested_in_the_change);  // function pointer
    n.add_observer(knows_the_previous_value()); // not a function pointer !

    // change value 
    n.change_value(30);
    std::cout << std::endl;
    n.change_value(20);
    return 0;
}


