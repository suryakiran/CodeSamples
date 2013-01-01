#include <std.hxx>
#include <boost-fusion.hxx>
#include <getopt.hxx>

namespace options {
  DEFINE_ARG(IntArg, int, "int", "Argument which takes an integer");
  DEFINE_ARG(StringArg, string, "string", "Argument which takes a string");

  typedef fusion::map <
    ARG(IntArg),
    ARG(StringArg)
      > TestArgs;
}

int main (int argc, char** argv)
{
  GetOpt<options::TestArgs> clOptions (argc, argv);
  clOptions.parseCommandLineOptions();

  fs_path_optional s = clOptions.getArgumentValue<options::CurrentSourceDir>();
  if (s) {
    cout << s.get() << endl;
  }

  clOptions.getArgumentValue<options::Help>();

#if 0
  bool b = clOptions.getArgumentValue <options::Help>();
  cout << boolalpha ;
  if (b) {
    cout << b.get() << endl;
  } else {
    cout << "NO ARGUMENT" << endl;
  }
#endif
}
