#include <iostream>
#include <vector>
#include <boost/assign/std/vector.hpp>
#include <boost/lambda/bind.hpp>
#include <boost/lambda/lambda.hpp>
using namespace std;
using namespace boost::assign;
using namespace boost::lambda;

int main (void)
{
  vector<int> vi;
  vi += 10, 2, 3, 15, 30, 1, 5, 40, 12, 11, 50, 34, 20, 18, 80;

  cout << vi.size() << endl;

  for (int i = 1; i < vi.size(); ++i)
  {
    int tmp = vi[i];
    int j = i - 1;
    while (tmp < vi[j] && j >= 0)
    {
      vi[j+1] = vi[j];
      j --;
    }
    vi[j+1] = tmp;
  }

  for_each (vi.begin(), vi.end(), cout << _1 << ',');
  cout << endl;
}
