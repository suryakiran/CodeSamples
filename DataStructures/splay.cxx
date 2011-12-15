#include <iostream>
#include <iomanip>
#include <splay.hpp>
using namespace std;

int main (void)
{
  cout << boolalpha;
  splay b;
  b += 10, 5, 25, 30, 15, 4, 24, 26, 35, 1, 14, 3, 40, 50, 60, 6, -1, -2, 34, 32, 33, 38, 45, 21, 22, 27, 28;
  b.print("Insertion Done");
  b.find (14);
  b.print ("Search 14");

//  cout << "Searching 14: " << b.find(14) << endl;
 // b.print ("Searched 14");
//  cout << "Searching 35: " << b.find(35) << endl;
 // b.print ("Searched 35");

 // b.remove (25);
 // b.print ("Deleted 25");
 // b.remove (5);
 // b.print ("Deleted 5");
 // b.remove (35);
 // b.print ("Deleted 35");
 // b.remove (4);
 // b.print ("Deleted 4");

 // cout << "Searching 24: " << b.find(24) << endl;
 // b.print ("Searched 24");
 // cout << "Searching 36: " << b.find(36) << endl;
 // b.print ("Searched 36");
}
