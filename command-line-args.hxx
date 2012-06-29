#ifndef command_line_args_hxx_INCLUDED
#define command_line_args_hxx_INCLUDED

#include <std.hxx>
#include <boost-fusion.hxx>

#include <boost/program_options.hpp>
namespace po = boost::program_options;

#include <boost/filesystem/path.hpp>
namespace fs = boost::filesystem;

namespace args {
  struct NoArgs{};
  struct OptionTakeNoValue{};
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

DEFINE_ARG(SourceDir, fs::path, "srcdir", "Source Directory");
DEFINE_ARG(BinaryDir, fs::path, "bindir", "Binary Directory");
DEFINE_ARG(CurrentSourceDir, fs::path, "cur_srcdir", "Current Source Directory");
DEFINE_ARG(CurrentBinaryDir, fs::path, "cur_bindir", "Current Binary Directory");
DEFINE_ARG(Help, OptionTakeNoValue, "help", "Help");

#define ARG(ArgName) detail::fusion_pair<ArgName>::type

  typedef fusion::map <
    ARG(SourceDir), 
    ARG(BinaryDir), 
    ARG(CurrentSourceDir), 
    ARG(Help),
    ARG(CurrentBinaryDir)
      > CommonArgsDesc;
}

namespace args {

  template <class ArgValueType>
    struct add_option_t
    {
      template <class ArgNameType>
        void operator()(po::options_description& p_desc, const ArgNameType& arg_name) const
        {
          p_desc.add_options()
            (arg_name.key(), po::value<ArgValueType>(), arg_name.description());
        }
    };

  template <>
    struct add_option_t<void>
    {
      template <class ArgNameType>
        void operator()(po::options_description& p_desc, const ArgNameType& arg_name) const
        {
          p_desc.add_options()
            (arg_name.key(), arg_name.description());
        }
    };

  template <>
    struct add_option_t<args::OptionTakeNoValue>
    {
      template <class ArgNameType>
        void operator()(po::options_description& p_desc, const ArgNameType& arg_name) const
        {
          p_desc.add_options()
            (arg_name.key(), arg_name.description());
        }
    };

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

      add_option_t<arg_value_type> add_option;
      add_option (m_desc, arg_name);
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
