#ifndef ParseArgs_hxx_INCLUDED
#define ParseArgs_hxx_INCLUDED

#include <map>
#include <string>
#include <DllParseArgs.hxx>

typedef std::map<std::string, std::string> Args;

class DLLParseArgs ParseArgs
{
  public:
    ParseArgs (int argc, char** argv)
      : m_argc(argc), m_argv(argv) { }

    const Args& operator() ();

  private:
    Args m_args;
    int m_argc;
    char** m_argv;
};

#endif
