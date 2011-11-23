#include <std.hxx>

int main (void)
{
  int a[] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20};
  int N = sizeof(a)/sizeof(int);
  int n = N/2;

  printContainer ("Before Swap:", a);

  for (int i = 1; i < n; ++i)
  {
    int k = n;
    for (int j = i; j < n; ++j, ++k)
    {
      swap (a[j], a[k]);
    }
  }

  printContainer ("After Swap:", a);
}
