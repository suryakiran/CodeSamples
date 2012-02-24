#include "std.hxx"

struct Top
{
  Top()
  {
    cout << "Top Constructor" << endl;
  }

  virtual void fun()
  {
    cout << "Function in Top" << endl;
  }
};

struct MiddleLeft : public virtual Top
{
  MiddleLeft()
  {
    cout << "MiddleLeft Constructor" << endl;
  }

  virtual void fun()
  {
    cout << "Function In MiddleLeft" << endl;
  }
};

struct MiddleRight : public virtual Top
{
  MiddleRight()
  {
    cout << "MiddleRight Constructor" << endl;
  }

  virtual void fun()
  {
    cout << "Function In MiddleRight" << endl;
  }
};

struct Bottom : public MiddleLeft, public MiddleRight
{
  Bottom()
  {
    cout << "Bottom Constructor" << endl;
  }

  virtual void fun()
  {
    MiddleRight::fun();
    MiddleLeft::fun();
  }
};

int main (void)
{
  Bottom b;
  b.fun();
}
