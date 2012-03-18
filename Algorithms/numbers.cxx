#include <std.hxx>

int reverse(int num)
{
  int n (num);
  int power (0);

  while ( n > 10 )
  {
    power ++;
    n /= 10;
  }

  n = num;
  int newNum (0);
  while (power)
  {
    int rem = n % 10;
    n /= 10;
    newNum += rem * static_cast<int>(pow (10, power--));
  }
  newNum += n;
  return newNum;
}

int reverse_new (int num)
{
  int rev_num (0);

  while (num)
  {
    rev_num = rev_num * 10 + (num % 10);
    num /= 10;
  }

  return rev_num;
}

char* toString (int num)
{
  int numChars (1);
  int n(num);
  if (num < 0) {
    numChars ++;
    n = -1 * num;
  }

  while (n > 0) {
    numChars ++;
    n /= 10;
  }

  cout << numChars << endl;
  char* s = (char*) malloc (sizeof(char) * numChars);
  char *ns = s;

  int i (0);
  if (num < 0) {
    *ns++ = '-';
    n = -1 * num;
  }
  else {
    n = num;
  }

  while (n > 0)
  {
    *ns++ = n % 10 + '0';
    n /= 10;
  }

  s[numChars] = '\0';
  return s;
}

int main (void)
{
  int num (-246978);
  cout << "Number: " << num << endl;
  //cout << "Reverse: " << reverse(num) << endl;
  cout << "To String: " << toString (num) << endl;
  cout << reverse_new (1234567) << endl;
  string s ("AAB");
  int i = fromHex (s) ;
}
