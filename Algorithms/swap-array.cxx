#include <std.hxx>

int main (void)
{
  int a[] = {1, 3, 5, 7, 9, 2, 4, 6, 8, 10};
  int N = sizeof(a)/sizeof(int);
  int n = N/2;

  printContainer ("Before Swap:", a);

  for (int i = 1; i < n; ++i)
  {
    for (int j = i; j < n; ++j)
    {
      swap (a[j], a[n+j]);
    }
  }

  printContainer ("After Swap:", a);
}
