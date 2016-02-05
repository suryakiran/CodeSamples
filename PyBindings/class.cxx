#include "class.hpp"
#include <iostream>
using namespace std;

Class::Class()
{
    cout << "Class Constructor" << endl;
}

std::string
Class::test()
{
    return "Class::test";
}

void
Class::args(int a, int b)
{
    cout << "***** Class::args" << endl;
    cout << "A: " << a << ", B: " << b << endl;
}

void
Class::defargs(int a, int b)
{
    cout << "***** Class::defargs" << endl;
    cout << "A: " << a << ", B: " << b << endl;
}

int
Class::defargsreturn(int a, int b, int c)
{
    cout << "***** Class::defargs" << endl;
    cout << "A: " << a << ", B: " << b << ", C: " << b << endl;
    return b;
}
