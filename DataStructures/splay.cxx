#include <iostream>
#include <iomanip>
#include <splay.hpp>
using namespace std;

int main (void)
{
  cout << boolalpha;
  splay b;
  b += 10, 5, 25, 30, 15, 4, 24, 26, 35, 1, 14, 3, 40, 50, 60, 6, -1, -2, 34, 32, 33, 38, 45, 21, 22, 27, 28, 70, 80, 20;
  b.print((fmt ("Insertion Done (%1% items)") % b.size()).str());
  b.find (14);
  b.print ("Search 14");
}
