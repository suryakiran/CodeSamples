#ifndef command_line_args_hxx_INCLUDED
#define command_line_args_hxx_INCLUDED

#include <std.hxx>
#include <boost-fusion.hxx>

#include <boost/program_options.hpp>
namespace po = boost::program_options;

namespace args {
  struct NoArgs;
}

#define DEFINE_ARG(ArgName, ValueType, ArgKey, ArgDesc) \
struct ArgName                                          \
{                                                       \
  typedef ValueType type;                               \
                                                        \
  const char* description() const {                     \
    return ArgDesc;                                     \
  }                                                     \
                                                        \
  const char* key() const {                             \
    return ArgKey;                                      \
  }                                                     \
}

namespace detail {
  template <class T>
    struct fusion_pair
    {
      typedef typename T::type value_type;
      typedef typename fusion::pair <T, value_type> type;
    };
}

namespace args {

DEFINE_ARG(SourceDir, string, "srcdir", "Source Directory");
DEFINE_ARG(BinaryDir, string, "bindir", "Binary Directory");
DEFINE_ARG(CurrentSourceDir, string, "cur_srcdir", "Current Source Directory");
DEFINE_ARG(CurrentBinaryDir, string, "cur_bindir", "Current Binary Directory");

#define ARG(ArgName) detail::fusion_pair<ArgName>::type

  typedef fusion::map <
    ARG(SourceDir), 
    ARG(BinaryDir), 
    ARG(CurrentSourceDir), 
    ARG(CurrentBinaryDir)
      > CommonArgsDesc;
}

namespace args {

  struct ArgumentProcessor
  {
    ArgumentProcessor (po::options_description& p_desc)
      : m_desc(p_desc)
    {
    }

    template <class T>
    void operator()(const T& argDesc) const
    {
      typedef typename T::first_type arg_name_type;
      typedef typename T::second_type arg_value_type;
      arg_name_type arg_name;

      m_desc.add_options()
        (arg_name.key(), po::value<arg_value_type>(), arg_name.description());
    }

    private:
      po::options_description& m_desc;
  };

  template <class T>
    struct Parser
    {
      typedef typename boost::add_reference<T>::type tref;
      Parser (tref p_argsDesc)
        : m_argsDesc(p_argsDesc)
      {
      }

      void parse (po::options_description& p_desc)
      {
        ArgumentProcessor argProcessor (p_desc);
        fusion::for_each (m_argsDesc, argProcessor);
      }

      private:
        tref m_argsDesc;
    };

  template <>
    struct Parser<args::NoArgs>
    {
      Parser (args::NoArgs&) { }
      void parse (po::options_description&) { }
    };
}

#endif
