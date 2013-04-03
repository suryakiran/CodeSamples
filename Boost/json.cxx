#include <std.hxx>
#include <boost.hxx>
#include <CommandLineArgs/ParseArgs.hxx>
#include <boost/filesystem.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
namespace fs = boost::filesystem;
using namespace boost::property_tree;

int main (int argc, char** argv)
{
  ParseArgs pa (argc, argv);
  Args args = pa();
  fs::path jsonFile (args["cur_src_dir"]);
  jsonFile /= "test.json";
  if (!fs::exists(jsonFile)) {
    exit(-1);
  }

  ptree pt;
  read_json(jsonFile.string(), pt);
  string s = pt.get<string>("pam.caching.proxy", "surya");
  cout << boolalpha ;
  cout << s << endl;
}
