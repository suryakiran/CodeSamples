#include "std.hxx"

bool bin_srch (int arr[], int beg, int end, int val)
{
  if (beg == end) {
    return false;
  }

  int middle = (beg + end) / 2;
  cout << fmt("Searching between [%1%, %3%, %2%]") % arr[beg] % arr[end] % arr[middle]<< endl;
  if (arr[middle] < val) {
    return bin_srch (arr, middle + 1, end, val);
  } else if (arr[middle] > val) {
    return bin_srch (arr, beg, middle-1, val);
  }

  return true;
}

int main (void)
{
  int arr[15];

  for (int i = 0; i < 15; ++i) {
    arr[i] = i*i;
  }

  printContainer ("Array", arr);
  cout << boolalpha << bin_srch (arr, 0, 14, 10) << endl;
  return 0;
}
