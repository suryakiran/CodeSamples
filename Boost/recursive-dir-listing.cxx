#include <std.hxx>
#include <boost.hxx>
#include <CommandLineArgs/ParseArgs.hxx>
#include <boost/filesystem.hpp>
namespace fs = boost::filesystem;

int main (int argc, char** argv)
{
  ParseArgs pa(argc, argv);
  Args args = pa();
  fs::path dir (args["cur_bin_dir"]);
  fs::recursive_directory_iterator rdiBegin(dir), rdiEnd;
  while(rdiBegin != rdiEnd) {
    cout << *rdiBegin << endl;
    ++rdiBegin;
  }
}
