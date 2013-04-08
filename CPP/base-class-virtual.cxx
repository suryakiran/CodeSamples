#include <std.hxx>

struct Base
{
  Base()
  {
  }

  virtual void test() = 0;
  virtual ~Base() {}
};

struct Derived : public Base
{
  Derived()
  {
  }

  virtual void test () {
    testImp();
  }

  virtual void testImp()
  {
    cout << "Derived::Test" << endl;
  }

  virtual ~Derived() { }
};

struct Der2 : public Derived
{
  Der2 () {
  }

  virtual void test() {
    testImp();
  }

  virtual ~Der2 () {}
};

int main (void)
{
  Base* derived = new Derived;
  Base* der2 = new Der2;

  Derived* d = dynamic_cast<Derived*>(der2);
  
  derived->test();
  der2->test();
  
  if (d) {
    d->test();
  }
}
