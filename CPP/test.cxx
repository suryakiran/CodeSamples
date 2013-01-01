#include "std.hxx"

int main (void)
{
  vector<int> vi;
  vector<unsigned int> vu;
  vi += 1,2,3,4,5;
  printContainer("Integers", vi);
  copy(vi.begin(), vi.end(), back_inserter(vu));
  printContainer("Unsigned Integers", vu);
}
