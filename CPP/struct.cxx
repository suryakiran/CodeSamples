#include <std.hxx>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>

struct test { };

typedef char yes;
typedef char (&no)[2];

template <class T>
struct is_struct
{
  template <class U>
  static yes tester (int U::*arg);

  template <class U>
  static no tester (...);

  static bool const value = 
    sizeof(tester<T> (0)) == sizeof (yes); 

  typedef boost::mpl::bool_<value> type;
};

int main (void)
{
  cout << boolalpha;
  cout << "Struct Example" << endl;
  cout << is_struct <test>::value << endl;
  cout << is_struct <int>::value << endl;
}
