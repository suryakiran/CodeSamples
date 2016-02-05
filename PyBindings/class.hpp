#ifndef class_hpp_INCLUDED
#define class_hpp_INCLUDED

#include<string>

struct Class {
    Class();

    std::string test();
    void args(int a, int b);
    void defargs(int a, int b = 23);
    int defargsreturn (int a, int b = 25, int c = 33);
};

#endif /* class_hpp_INCLUDED */
