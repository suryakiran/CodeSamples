#include "std.hxx"

int* incr (int arr[], int sz)
{
  int *ret = 0;
  int num (0);
  for (int i = 0; i < sz; ++i)
  {
    num = (num * 10) + arr[i];
  }
  num++;
  cout << num << endl;
  return ret;
}

int main (void)
{
  int a[] = {9,9,9,9};
  int* b = incr (a, sizeof(a)/sizeof(int));
}
