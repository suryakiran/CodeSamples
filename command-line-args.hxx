#ifndef command_line_options_hxx_INCLUDED
#define command_line_options_hxx_INCLUDED

#include <std.hxx>
#include <boost-fusion.hxx>

#include <boost/program_options.hpp>
namespace po = boost::program_options;

#include <boost/filesystem/path.hpp>
namespace fs = boost::filesystem;

namespace options {
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
    struct add_option_t<options::OptionTakeNoValue>
    {
      template <class ArgNameType>
        void operator()(po::options_description& p_desc, const ArgNameType& arg_name) const
        {
          p_desc.add_options()
            (arg_name.key(), arg_name.description());
        }
    };
}

namespace options {

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

  template <class T>
    struct Parser
    {
      typedef typename boost::add_reference<T>::type tref;
      Parser (tref p_optionsDesc)
        : m_optionsDesc(p_optionsDesc) { }

      void parse (po::options_description& p_desc)
      {
        fusion::for_each (m_optionsDesc, option_processor(p_desc));
      }

      private:
        struct option_processor
        {
          option_processor (po::options_description& p_desc)
            : m_desc(p_desc) { }

          template <class ArgNameType, class ArgValueType>
            void
            add_option (const ArgNameType& p_name, const ArgValueType& p_type) const
            {
              detail::add_option_t<ArgValueType> v;
              v(m_desc, p_name);
            }

          template <class option>
            void operator()(const option& argDesc) const
            {
              typedef typename option::first_type opt_name_type;
              typedef typename option::second_type opt_value_type;

              opt_name_type opt_name;
              opt_value_type opt_value;

              add_option (opt_name, opt_value);
            }

          private:
          po::options_description& m_desc;
        };

        tref m_optionsDesc;
    };

  template <>
    struct Parser<options::NoArgs>
    {
      Parser (options::NoArgs&) { }
      void parse (po::options_description&) { }
    };
}

#endif
