#include "std.hxx"
#include <boost/variant.hpp>

typedef vector<string> int_vector;
typedef boost::variant <int, bool, float, string, int_vector> variant_type;

struct Test
{
  variant_type mVar;

  Test()
  {
    mVar = string("Test String");
  }

  const variant_type& value() const {
    return mVar;
  }
};

int main (void)
{
  Test t;
  const variant_type& vRef = t.value();
  variant_type vCopy = vRef;
  cout << "Variant Test" << endl;
}
