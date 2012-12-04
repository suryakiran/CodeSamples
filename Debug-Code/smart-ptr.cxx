#include "std.hxx"
#include <boost/shared_ptr.hpp>

typedef vector<string> int_vector;
typedef boost::shared_ptr<int> sp_int;
typedef boost::shared_ptr<float> sp_float;
typedef boost::shared_ptr<string> sp_string;

int main (void)
{
  const sp_int si (new int(5));
  const sp_float sf (new float(12.3));
  sp_string ss (new string ("Surya Kiran Gullapalli"));
  sp_int nsi;
  cout << *si << '\t' << *sf << '\t' << *ss << endl;
}
