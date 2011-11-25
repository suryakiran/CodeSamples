// Find the next palindrome number which is greater than or equal to a given number
// For example, given number is 1235, then next palindrome number is 1331.
// Approach is if number - reverse of number == 0, then number is palindrom. Hence we will keep increasing the number till it meets the condition.


#include <iostream>
#include <math.h>
using namespace std;

int Reverse(int n)
{
  if (n < 0) {
    throw exception();
  }

  int temp(0), power(0);

  // first calculate number of digits
  int num = pow(10, power);

  while (n / num != 0)
  {
    power++;
    num = (int)pow(10, power);
  }

  int rem = 0;
  // now use modulo operator to reverse the number
  for (int i = 0; i < power; i++)
  {
    temp += (n % 10) * (int)pow (10, power-i-1);
    n = n / 10;
  }

  return temp;
}

int main()
{
  int n = 102;
  while (n - Reverse(n) != 0)
  {
    cout << "Current number is: " << n << endl;
    n++;
  }

  cout << n << endl;
  return 0;
}
