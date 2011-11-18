#include <iostream>
#include <iomanip>
#include <binary_tree.hpp>
using namespace std;

int main (void)
{
  cout << boolalpha;
  bst b;
  b += 10, 5, 25, 30, 15, 4, 24, 26, 35, 1, 14, 3;
  b.print();

  cout << "Minimum: " << b.findMin() << endl;
  cout << "Maximum: " << b.findMax() << endl;
  cout << "Searching 24: " << b.find(24) << endl;
  cout << "Searching 35: " << b.find(35) << endl;

  b.remove (25);
  b.remove (5);
  b.remove (35);
  b.remove (4);
  b.print();

  cout << "Minimum: " << b.findMin() << endl;
  cout << "Maximum: " << b.findMax() << endl;
  cout << "Searching 24: " << b.find(24) << endl;
  cout << "Searching 35: " << b.find(35) << endl;
}
