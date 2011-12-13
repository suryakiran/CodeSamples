#include <dlist.hpp>

int main (void)
{
  dlist d;
  for (int i = 0; i < 10; ++i) {
    d.push(i);
  }
  d.reverse();
  d.print();
}
