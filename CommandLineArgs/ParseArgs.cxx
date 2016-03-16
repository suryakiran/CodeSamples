#include <ParseArgs.hxx>
#include <boost/program_options.hpp>
#include <iostream>
using namespace boost::program_options ;

const Args&
ParseArgs::operator() ()
{
  options_description desc ("Allowed Options") ;
  desc.add_options()
    ("help",           "Show this message")
    ("srcdir",  value <string>(), "CMake Source Dir")
    ("cur_srcdir",   value <string>(), "CMake Current Source Dir")
    ("bindir",     value <string>(), "CMake Bin Dir")
    ("cur_bindir",     value <string>(), "CMake Current Bin Dir")
    ;

  variables_map vm ;
  try
  {
    store (parse_command_line (m_argc, m_argv, desc), vm) ;
    notify (vm) ;
  }
  catch( std::exception& e)
  {
    cout << "Exception in reading command line variables: " << e.what() << endl ;
  }

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
}
