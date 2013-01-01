#include <std.hxx>
#include <boost/unordered_map.hpp>

int main (void)
{
    cout << BOOST_VERSION << endl;
  typedef boost::unordered_map<string, float> Map;
  Map m;
  m["ABC"] = 1.0f;
  m["PQR"] = 2.0f;
  m["XYZ"] = 3.0f;
  Map::iterator it = m.find("ABC");
  cout << it->first << endl;
  
  it = m.find("abc");
  cout << "it not found" << endl;


}
