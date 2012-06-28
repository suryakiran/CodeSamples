#ifndef getopt_hxx_INCLUDED
#define getopt_hxx_INCLUDED

#include "command-line-args.hxx"

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
      po::variables_map vm ;
      try
      {
        po::store (po::parse_command_line (m_argc, m_argv, m_desc), vm) ;
        po::notify (vm) ;
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
    po::options_description m_desc;
    int m_argc;
    char** m_argv;
    args::CommonArgsDesc m_commonArgsDesc;
    AppArgsDesc m_appArgsDesc;
};

#endif
