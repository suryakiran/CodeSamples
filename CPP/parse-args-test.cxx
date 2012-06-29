#include <std.hxx>
#include <boost-fusion.hxx>
#include <getopt.hxx>

namespace args {
  DEFINE_ARG(IntArg, int, "int", "Argument which takes an integer");
  DEFINE_ARG(StringArg, string, "string", "Argument which takes a string");

  typedef fusion::map <
    ARG(IntArg),
    ARG(StringArg)
      > TestArgs;
}

int main (int argc, char** argv)
{
  GetOpt<args::TestArgs> clOptions (argc, argv);
  clOptions.parseCommandLineOptions();

  fs::path s = clOptions.getArgumentValue<args::CurrentSourceDir>();
  cout << s << endl;
}
