#ifndef CommandLineArgs_hxx_INCLUDED
#define CommandLineArgs_hxx_INCLUDED

#include <sstream>
#include <vector>
#include <string>
#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;
using namespace std;

class CommandLineArgs
{
  public:
    CommandLineArgs();
    ~CommandLineArgs();

    int count() const;

    void add (const fs::path& p_path)
    {
      m_args.push_back (p_path.string());
    }

    template<class T>
    void add(const T& p_arg)
    {
      ostringstream os ;
      os << p_arg;
      m_args.push_back(os.str());
    }

    char** operator()() ;

  private:
    vector<string> m_args;
    char** m_argv;
};

#endif
