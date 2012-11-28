#include "std.hxx"
#include <boost/variant.hpp>

typedef vector<string> int_vector;
typedef boost::variant <int, bool, float, string, int_vector> variant_type;

int main (void)
{
  variant_type vi, vb, vf, vs;
  int i(5);
  vector<string> viv ;
  viv += "A", "B", "C", "D";
  vs = string("Surya Kiran");
  vs = viv;
  vi = 10;
  vb = true;
  vf = 1.234f;
  cout << "Variant Test" << endl;
}
