#include <std.hxx>

struct Test
{
  Test() {
    cout << "Test Constructor" << endl;
  }

  void fun() {
    cout << "Test::fun" << endl;
  }

  ~Test() {
    cout << "Test Destructor" << endl;
  }
};

int main (void)
{
  auto_ptr <Test> t1(new Test);
  auto_ptr <Test> t2 (t1);
}
