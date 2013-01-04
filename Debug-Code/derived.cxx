#include <std.hxx>

class Base
{
public:
  Base() : mBase(5) { }
  virtual ~Base() { }
  int mBase;
};

class DerivedA : public Base
{
public:
  DerivedA() : Base(), mDerivedA(10) { }
  virtual ~DerivedA() { }
  int mDerivedA;
};

class DerivedB : public DerivedA
{
public:
  DerivedB() : DerivedA(), mDerivedB(15) { }
  virtual ~DerivedB() { }
  int mDerivedB;
};

int main (void)
{
  Base* b = new Base;
  Base *dA = new DerivedA();
  DerivedA *dB = new DerivedB();
  cout << "Derived Test" << endl;
}
