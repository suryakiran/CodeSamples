#include <std.hxx>

int main (void)
{
  int num (21435968);
  cout << "Actual Number: " << num << endl;
  vector<int> vi;

  while (num)
  {
    vi.push_back (num % 10);
    num /= 10;
  }

  printContainer ("Vector", vi);
  make_heap (vi.begin(), vi.end(), std::greater<int>());
  printContainer ("Vector", vi);

  stable_sort (vi.begin(), vi.end());
  printContainer ("Vector, after sort", vi);

#if 0
  int power(0);
  int n (0);
  while (!vi.empty())
  {
    n += vi[0] * static_cast<int> (pow (10, power++));
    cout << vi[0] << ',';
    pop_heap (vi.begin(), vi.end(), std::greater<int>());
    vi.pop_back();
  }
  cout << endl;
  cout << n << endl;
#endif
}
