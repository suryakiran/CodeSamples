#include <std.hxx>

struct Test
{
  Test() {
    
  }

  void fun(const int& i) const
    {
      cout << "Integer: " << i << endl;
    }
};

int main (void)
{
  cout << "Bind Example" << endl;
  Test t;
  auto f = boost::lambda::bind(&Test::fun, t, boost::lambda::_1);
  f(10);
}
