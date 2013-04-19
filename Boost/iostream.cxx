#include <std.hxx>
#include <boost.hxx>

#include <boost/iostreams/categories.hpp>
#include <boost/iostreams/positioning.hpp>
#include <boost/iostreams/concepts.hpp>
namespace io = boost::iostreams;

class my_device : public io::seekable
{
  
};

int main (void)
{
  cout << "Boost Iostream Example" << endl;
}
