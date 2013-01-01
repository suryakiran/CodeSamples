#include "std.hxx"

struct Test
{
  Test()
  { cout << BOOST_CURRENT_FUNCTION << endl; }

  void fun () {
    cout << BOOST_CURRENT_FUNCTION << endl;
  }

  virtual void fun (int) __attribute__ ((deprecated)) {
    cout << BOOST_CURRENT_FUNCTION << endl;
  }
};

struct Derived : public Test
{
  Derived() {
    cout << BOOST_CURRENT_FUNCTION << endl;
  }

  virtual void fun (int) {
    cout << BOOST_CURRENT_FUNCTION << endl;
  }
};

int main (void)
{
  Test *t = new Derived;
  t->fun(5);

  typedef decltype (t->fun()) test_fun_type;
  cout << typeid (test_fun_type).name() << endl;
}
