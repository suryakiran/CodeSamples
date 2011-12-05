#include <heap.hpp>

int main (void)
{
  vector<int> vi;
  vi += 9, 8, 10, 15, 7, 22, 25, 30 ;
  heap<int> h (vi);
  h.print();
  h.add (6);
  h.print();
  h.add (1);
  h.print();
}
