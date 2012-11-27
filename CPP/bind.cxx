#include "std.hxx"
#include <boost/phoenix.hpp>
namespace phx = boost::phoenix;

typedef void (*funp)();

struct Test
{
  Test () { }
  void fun() {
    cout << "Test Function" << endl; 
  }
};

struct Temp
{
  Temp() { }
  void fun() { 
    cout << "Temp Function" << endl; 
  }
};

template <class T, class Obj>
struct Fun
{
  Fun (T& t, Obj& o)
    :m_t(t), m_o(o)
  {
  }

  void
  operator ()()
  {
    m_o(m_t);
  }

  T m_t;
  Obj m_o;
};

template <class T>
void freeFunction (T f)
{
  f();
}

int main (void)
{
  Test test;
  Temp temp;

//  typedef void (Test::*pf)();
 // pf = &Test::fun; 
  //test.pf();

  auto mf = mem_fun_ref (&Test::fun);

  Fun < Test, mem_fun_ref_t<void, Test> > f (test, mf);
  freeFunction (f);
}
