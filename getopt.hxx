#ifndef getopt_hxx_INCLUDED
#define getopt_hxx_INCLUDED

#include "command-line-args.hxx"
#include <boost/utility/enable_if.hpp>
#include <boost/utility/value_init.hpp>
#include <boost/scoped_ptr.hpp>

namespace arg_types {
  struct invalid { };
}

template <class AppArgsDesc>
class GetOpt
{
  typedef fusion::joint_view<args::CommonArgsDesc, AppArgsDesc> AllArgs;
  public:
    GetOpt(int argc, char** argv)
      : m_argc(argc), m_argv(argv)
    {
      args::Parser<args::CommonArgsDesc> commonArgsParser(m_commonArgsDesc);
      commonArgsParser.parse (m_desc);

      args::Parser<AppArgsDesc> appArgsParser (m_appArgsDesc);
      appArgsParser.parse(m_desc);
    }

    void parseCommandLineOptions()
    {
      try
      {
        po::store (po::parse_command_line (m_argc, m_argv, m_desc), m_varMap) ;
        po::notify (m_varMap) ;
      }
      catch( std::exception& e)
      {
        cout << "Exception in reading command line variables: " << e.what() << endl ;
      }
    }

  private:
    template <class ArgName>
    struct has_key 
      : fusion::result_of::has_key<AllArgs, ArgName> { };

    template <class ArgName>
      struct at_key
      {
        typedef typename fusion::result_of::at_key<AllArgs, ArgName>::type arg_type;
        typedef typename boost::remove_reference<arg_type>::type type;
      };

  public:
    template <class T>
      typename boost::enable_if_c <has_key <T>::value, typename at_key<T>::type >::type
      getArgumentValue()
      {
        typedef typename at_key<T>::type return_type;
        boost::value_initialized<return_type> t;
        T arg;
        if (m_varMap.count(arg.key())) {
          return m_varMap[arg.key()].template as<return_type>();
        }
        return t.data();
      }

  private:
    po::options_description m_desc;
    int m_argc;
    char** m_argv;
    args::CommonArgsDesc m_commonArgsDesc;
    AppArgsDesc m_appArgsDesc;
    po::variables_map m_varMap;
};

#endif
