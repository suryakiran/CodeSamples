#include <boost/variant.hpp>
#include <std.hxx>

typedef const char* cptr;
typedef boost::variant<int, cptr, std::string> Variant;

struct print : public boost::static_visitor<void>
{
  void operator() (cptr item)
    {
      cout << "Const Char*" << endl;
    }

  void operator() (const string& s)
    {
      cout << "String" << endl;
    }

  void operator() (int i)
    {
      cout << "Int" << endl;
    }
};
  
int main (void)
{
  Variant v;
  v = "Surya";
  print p;
  boost::apply_visitor(p, v);
  v = 1;
  boost::apply_visitor(p, v);
  v = std::string("Abc");
  boost::apply_visitor(p, v);
}
