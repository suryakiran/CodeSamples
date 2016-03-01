#include <iostream>
#include <QtCore/QVariant>
#include <json/json.h>

#include <list>
#include <string>
#include <vector>
#include <set>
#include <type_traits>

#include <boost/assign.hpp>

#include "dumper.hxx"

using namespace boost::assign;

struct Test
{
    Test() : i(-1) {}
    Test(int a): i(a) {}
    int i;

};

std::ostream&
operator<< (std::ostream& os, const Test& test){
    os << test.i ;
    return os;
}

Q_DECLARE_METATYPE(Test)

int main (void)
{
    std::cout << "----- BEGIN -----"  << std::endl;

    std::cout << "Is Test Streamable: " << IsStreamable<Test>::value << std::endl;
    std::cout << "QVariant:" << std::endl;
    QVariantList var;
    var << 3.4 << 4.5 << 5.6 << 6.7;
    DumpUtils::dump(var);

    std::cout << "" << std::endl;
    std::cout << "QVariantMap:" << std::endl;
    QVariantMap map;
    map["Surya"] = QStringList() << "a" << "b" << "c" ;
    QVariantMap submap;
    submap["1"] = "One";
    submap["2"] = "Two";
    submap["3"] = "Three";
    map["Kiran"] = submap;
    map["Gullapalli"] = 1;
    DumpUtils::dump(map);

    
    std::cout << "" << std::endl;
    std::cout << "std::list<std::string>:" << std::endl;
    std::list<std::string> ls = {"Surya", "kiran", "Gullapalli"};
    DumpUtils::dump(ls);

    std::cout << "" << std::endl;
    std::set<std::string> ss;
    std::cout << "std::set<std::string>: " << std::endl;
    insert(ss) ("Surya") ("Kiran") ("Gullapalli");
    DumpUtils::dump(ss);

    std::cout << "" << std::endl;
    std::cout << "std::vector<int>:" << std::endl;
    std::vector<int> vi = {1, 2, 3, 4, 5};
    DumpUtils::dump(vi);

    std::cout << "" << std::endl;
    std::cout << "std::deque<int>:" << std::endl;
    std::deque<int> di;
    di += 1,2,3,4,5;
    DumpUtils::dump(di);

    typedef std::vector<int> Vector;
    typedef std::map<std::string, int> Map;
    std::cout << "" << std::endl;
    std::cout << "std::map<std::string, int>:" << std::endl;
    std::map<std::string, int> sm;
    sm["surya"] = 1;
    sm["kiran"] = 2;
    sm["gullapalli"] = 3;
    DumpUtils::dump(sm);

    std::cout << "----- END -----"  << std::endl;
}
