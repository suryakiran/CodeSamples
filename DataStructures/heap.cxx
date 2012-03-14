#include <heap.hpp>

int main (void)
{
  vector<int> vi;
  vi += 5, 10, 15, 20, 25, 30, 35, 40, 45, 50;
  heap<int> h (vi);
  h.print("Initial Heap");
  //h.add (6);
  //h.print("Added 6");
  //h.add (1);
  //h.print("Added 1");
  //h.add (11);
  //h.print("Added 11");
  //h.add (5);
  //h.print("Added 5");
  //h.sort();
  //h.print("Sorted Heap");
}
