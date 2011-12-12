#include <iostream>
#include <iomanip>
#include <binary_tree.hpp>
using namespace std;

int main (void)
{
  cout << boolalpha;
  bst b;
  b += 10, 5, 25, 30, 15, 4, 24, 26, 35, 1, 14, 3, 6;

  b.printToDot ("current-tree.dot");

  cout << "Tree is mirror image: " << b.isMirrorImage() << endl;
  /*
  b.remove (25);
  b.remove (5);
  b.remove (35);
  b.remove (4);
  b.print();
  */
//  b.print();
//  b.traverseZigZag();
//  b.sumLeftRight();
 // b.print();
 // cout << "Common Ancestor of 24, 25: " << b.commonAncestor (24, 25) << endl;
 b.toLinkedList();
}
