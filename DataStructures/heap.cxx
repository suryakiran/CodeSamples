#include <heap.hpp>

int main (void)
{
  vector<int> vi;
  vi += 9, 8, 10, 4, 3, 15, 7, 22, 25, 30, 1, 2;
  heap<int> h (vi);

  while (!h.empty())
  {
    cout << h.getMin() << endl;
    h.removeMin();
  }
//  h.print();
}
