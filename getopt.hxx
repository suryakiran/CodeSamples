#ifndef getopt_hxx_INCLUDED
#define getopt_hxx_INCLUDED

#include "command-line-args.hxx"
#include <boost/utility/enable_if.hpp>
#include <boost/utility/value_init.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/optional.hpp>

namespace arg_types {
  struct invalid { };
}

typedef boost::optional<fs::path> fs_path_optional;
typedef boost::optional<string> string_optional;
typedef boost::optional<int> int_optional;
typedef boost::optional<double> double_optional;

template <class AppArgsDesc>
class GetOpt
{
  typedef fusion::joint_view<options::CommonArgsDesc, AppArgsDesc> AllArgs;
  public:
    GetOpt(int argc, char** argv)
      : m_argc(argc), m_argv(argv)
    {
      options::Parser<options::CommonArgsDesc> commonArgsParser(m_commonArgsDesc);
      commonArgsParser.parse (m_desc);

      options::Parser<AppArgsDesc> appArgsParser (m_appArgsDesc);
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

    struct check_option_if_provided
    {
      template <class option_name>
      bool operator()()
      {
        return true;
      }
    };

    struct get_option_value
    {
      bool operator()()
      {
        return true;
      }
    };

    template <class ArgName>
      struct at_key
      {
        typedef typename fusion::result_of::at_key<AllArgs, ArgName>::type arg_type;
        typedef typename boost::remove_reference<arg_type>::type no_ref_type;

        typedef typename 
          mpl::or_ < 
          typename boost::is_void<no_ref_type>::type, 
                   typename boost::is_same<no_ref_type, options::OptionTakeNoValue>::type 
                     >::type arg_take_no_value_type;

        typedef typename
          mpl::eval_if <
          arg_take_no_value_type, 
          mpl::identity<bool>, 
          mpl::identity<no_ref_type> 
            >::type value_type;

        typename mpl::eval_if <
          arg_take_no_value_type,
          mpl::identity<check_option_if_provided>,
          mpl::identity<get_option_value>
            >::type option_extractor_type;

        typedef boost::optional<value_type> return_type;

        at_key()
        {
          cout << typeid(option_extractor_type).name() << endl;
        }
      };

  public:
    template <class T>
      typename boost::enable_if_c <has_key <T>::value, typename at_key<T>::return_type >::type
      getArgumentValue()
      {
        typedef typename at_key<T>::return_type return_type;
        typedef typename at_key<T>::value_type value_type;
        typedef typename at_key<T>::no_ref_type no_ref_type;

        at_key<T> a;

        T arg;
        if (m_varMap.count(arg.key())) {
          return return_type(m_varMap[arg.key()].template as<value_type>());
        }
        return return_type();
      }

  private:
    po::options_description m_desc;
    int m_argc;
    char** m_argv;
    options::CommonArgsDesc m_commonArgsDesc;
    AppArgsDesc m_appArgsDesc;
    po::variables_map m_varMap;
};

#endif
