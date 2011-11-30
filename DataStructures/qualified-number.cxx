#include <std.hxx>
/*
   A number is qualified is all its digits are in ascending order. Example: 123; 1<2<3. 
   Given the value on N, the number of digits in the number, print all the qualified numbers.
   */

int generate_number (int from, int numdigits)
{
  int sum (0);

  if (numdigits == 0) {
    return -1;
  }

  if (numdigits == 1) {
    for (int i = from; i < 9; ++i)
    {
      cout << i << endl;
    }
  }
  int g (generate_number (from+1, numdigits-1));
}

int main (void)
{
  int n (5);

  generate_number (1, 5);
}
