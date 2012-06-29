#ifndef getopt_hxx_INCLUDED
#define getopt_hxx_INCLUDED

#include "command-line-args.hxx"
#include <boost/utility/enable_if.hpp>

namespace arg_types {
  struct invalid { };
}

template <class AppArgsDesc>
class GetOpt
{
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

#if 0
      if (vm.count ("srcdir")) {
        m_args["src_dir"] = vm["srcdir"].as<string>();
      }

      if (vm.count ("cur_srcdir")) {
        m_args["cur_src_dir"] = vm["cur_srcdir"].as<string>();
      }

      if (vm.count ("bindir")) {
        m_args["bin_dir"] = vm["bindir"].as<string>();
      }

      if (vm.count ("cur_bindir")) {
        m_args["cur_bin_dir"] = vm["cur_bindir"].as<string>();
      }

      return m_args;
#endif
    }

  private:
    template <class ArgName, class Sequence>
    struct has_key 
      : fusion::result_of::has_key<Sequence, ArgName> { };

    template <class ArgName, class Sequence>
      struct at_key
      {
        typedef typename fusion::result_of::at_key<Sequence, ArgName>::type key_type;
        typedef typename boost::remove_reference<key_type>::type type;
      };

  public:
    template <class T>
      typename boost::enable_if_c <has_key <T, args::CommonArgsDesc>::value, typename at_key<T, args::CommonArgsDesc>::type >::type
      getArgumentValue()
      {
        typedef typename at_key<T, args::CommonArgsDesc>::type type;
        cout << boolalpha << boost::is_same<type, string>::value << endl;
        type t;
        return t;
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
