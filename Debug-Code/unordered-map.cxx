#include <std.hxx>
#include <boost/unordered_map.hpp>

int main (void)
{
  typedef boost::unordered_map<string, float> Map;
  Map m;
  m["ABC"] = 1.0f;
  m["PQR"] = 2.0f;
  m["XYZ"] = 3.0f;
  Map::const_iterator it = m.find("ABC");
  it = m.find("abc");
  cout << "Unordered debug example" << endl;

}
