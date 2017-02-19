/*
 * boost::property_tree tutorial
 *
 * zdd / zddhub@gmail.com
 * https://github.com/zddhub/boost_tutorial
 */

#include <iostream>
#include <string>
using namespace std;

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

typedef boost::property_tree::ptree ptree;

//create JSON file
void write_json(const string& filename) {

    ptree boost_tutorial;
    boost_tutorial.put("name", "boost_tutorial");

    ptree author;
    author.put("name", "zdd");
    author.put("email", "zddhub@gmail.com");
    author.put("website", "zddhub.com");
    boost_tutorial.put_child("author", author);

    ptree content;
    content.push_back(std::make_pair("chapter1", "boost::thread"));
    content.push_back(std::make_pair("chapter2", "smart pointer"));
    content.push_back(std::make_pair("chapter3", "boost::property_tree"));

    //if key == null, is array, else is object
    ptree array;
    array.push_back(std::make_pair("", "boost::scoped_ptr"));
    array.push_back(std::make_pair("", "boost::shared_ptr"));
    array.push_back(std::make_pair("", "boost::weak_ptr"));
    content.put_child("chapter2", array);

    boost_tutorial.put_child("content", content);

    ostringstream os;
    boost::property_tree::write_json(os, boost_tutorial);
    cout << "JSON file: " <<endl;
    cout << os.str() <<endl;

    //write to file
    boost::property_tree::write_json(filename, boost_tutorial);
}

//parser JSON file
void read_json(const string& filename) {

    ptree boost_tutorial;
    boost::property_tree::read_json(filename, boost_tutorial);

    cout << "name:" << boost_tutorial.get<string>("name")<<endl;

    ptree author = boost_tutorial.get_child("author");
    cout << "name:" << author.get<string>("name")<<endl;
    cout << "email:" << author.get<string>("email")<<endl;
    cout << "website:" << author.get<string>("website")<<endl;

    ptree content = boost_tutorial.get_child("content");
    cout << "chapter1:" << content.get<string>("chapter1")<<endl;
    cout << "chapter2:" << content.get<string>("chapter2")<<endl;

    ptree array = content.get_child("chapter2");
    for(ptree::iterator it = array.begin(); it != array.end(); ++it) {
        //key: it->first.data(), value: it->second.data().
        //cout << " " << it->first.data()<<endl; //first is ""
        cout << "  " << it->second.get<string>("")<<endl;
        // cout << "\t" << it->second.data()<<endl; // ==
    }

    cout << "chapter3:" << content.get<string>("chapter3")<<endl;
}

int main()
{
    cout << "property tree: " << endl;
    cout << "parser JSON file as a example." <<endl;

    string filename = "boost_toturial.json";
    write_json(filename);

    read_json(filename);

    return 0;
}

