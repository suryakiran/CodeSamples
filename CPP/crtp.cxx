#include <std.hxx>

template<class T>
struct traits;

template <class der>
struct base
{
  typedef typename traits<der>::value_type value_type;

  value_type fun() {
    value_type v;
    return v;
  }
};

struct derived;
template <> struct traits<derived>
{
  typedef int value_type;
};

struct derived : public base<derived>
{
};

int main (void)
{
  derived d;
  d.fun();
}
