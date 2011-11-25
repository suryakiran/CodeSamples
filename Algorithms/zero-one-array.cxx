#include <std.hxx>

int main (void)
{
  int a[] = {1, 0, 1, 1, 1, 0, 1};
  int n = boost::size(a);
  int i (0), j (n-1);

  printContainer ("Original Container: ", a);

  while (i < j)
  {
    while (a[j] && j)
      j--;
    while (!a[i] && i<n)
      i++;

    if (i < j)
      swap(a[i], a[j]);
  }

  printContainer ("Modified Container: ", a);
}
