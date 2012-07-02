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

  fs_path_optional s = clOptions.getArgumentValue<args::CurrentSourceDir>();
  if (s) {
    cout << s.get() << endl;
  }

#if 0
  bool b = clOptions.getArgumentValue <args::Help>();
  cout << boolalpha ;
  if (b) {
    cout << b.get() << endl;
  } else {
    cout << "NO ARGUMENT" << endl;
  }
#endif
}
