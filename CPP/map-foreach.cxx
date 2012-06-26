#include "std.hxx"

struct Print
{
  void operator()(const stl::IntStringMapValue& v) const {
    cout << v.first << '\t' << v.second << endl;
  }
};

int main (void)
{
  stl::IntStringMap mis;
  insert(mis) (3, "Surya") (1, "Kiran") (2, "Gullapalli");
  for_each (mis.begin(), mis.end(), Print());
}
