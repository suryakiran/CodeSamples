#include <iostream>
#include <test/Example.h>
using namespace std;

int main (void)
{
  cout << "Example" << endl;

  Example e;
  e.setValue (103) ;

  cout << e.getValue() << endl;
  return 0;
}
