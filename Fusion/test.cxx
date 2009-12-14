#include <iostream>
#include <string>

#include <boost/signals2.hpp>
#include <boost/typeof/typeof.hpp>

#include <boost/fusion/container.hpp>
#include <boost/fusion/sequence/intrinsic.hpp>
#include <boost/fusion/functional/invocation/invoke.hpp>
#include <boost/fusion/functional.hpp>
#include <boost/fusion/iterator.hpp>
#include <boost/fusion/include/for_each.hpp>

#include <boost/lambda/lambda.hpp>
#include <boost/lambda/bind.hpp>
#include <boost/format.hpp>
using namespace std ;
using namespace boost ;
using boost::format ;

#include <boost/preprocessor/control/expr_if.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/iteration/local.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/repetition/enum_shifted_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_shifted_params.hpp>

//#undef BOOST_PP_ENUM_SHIFTED_BINARY_PARAMS
//#undef BOOST_PP_IF

#define MAX_SIGNAL_PARAMS 10

using boost::shared_ptr ;
using namespace boost ;
using namespace boost::signals2 ;
#define BOOST_SIGNAL(...) boost::shared_ptr< boost::signals2::signal < __VA_ARGS__ > >

#if 0
#define BOOST_PP_LOCAL_MACRO(n)\
	template<int id BOOST_PP_COMMA_IF(n) BOOST_PP_ENUM_PARAMS(n, typename T)> \
void func(BOOST_PP_EXPR_IF(n,const boost::fusion::vector##n<BOOST_PP_ENUM_PARAMS(n, T)>& p_args))\
{\
	cout << format("Number Of Arguments: %1%, Id: %2%") % n % id << endl ;\
}

#define BOOST_PP_LOCAL_LIMITS (0, MAX_ARGS)
#include BOOST_PP_LOCAL_ITERATE()

int main (void)
{
	func<10> (boost::fusion::make_vector(1, 2, 4, 5)) ;
	func<6> () ;

	return 0 ;
}
#endif



class MySignals
{
	private:
		typedef boost::fusion::vector <
            BOOST_SIGNAL(void(const int&, const string&))
            , BOOST_SIGNAL(void())
            , BOOST_SIGNAL(void(const string&))
            > SignalsVec ;

		SignalsVec m_signals ;

		typedef fusion::result_of::begin<SignalsVec>::type BeginIter ;
		typedef fusion::result_of::end<SignalsVec>::type EndIter ;

		template <int id>
		struct get_type
		{
			typedef typename fusion::result_of::value_of <
				typename fusion::result_of::advance_c<BeginIter, id>::type >::type::reference value_type ;
		} ;

        struct initialize
        {
            template <typename SmartPtr>
                void operator() (SmartPtr& p_item) const
                {
					typedef typename SmartPtr::value_type ItemType ;

					p_item = SmartPtr(new ItemType) ;
#if 0
					typedef typename fusion::result_of::value_of<
						fusion::result_of::advance_c<BeginIter, 2>::type >::type::value_type ValueType ;
					cout << typeid(get_type<StringSignal>::value_type).name() << endl ;
					cout << "---------------------" << endl ;
#endif
                }

        } ;

	public:
		static MySignals* instance (void) 
		{ 
			if (!m_instance) 
				m_instance = new MySignals ;
			return m_instance ; 
		}

		enum {
			IntStringSignal = 0,
			VoidSignal,
			StringSignal 
		} ;

	template <int id> 
		typename get_type<id>::value_type
			signal (void) { return *(fusion::at_c<id>(m_signals)) ; }

#define BOOST_PP_LOCAL_MACRO(n)\
	template<int id BOOST_PP_COMMA_IF(n) BOOST_PP_ENUM_SHIFTED_PARAMS(BOOST_PP_INC(n), typename T)> \
	void emitSignal(\
            BOOST_PP_IF(n, BOOST_PP_ENUM_SHIFTED_BINARY_PARAMS, void BOOST_PP_TUPLE_EAT(3))\
            (BOOST_PP_INC(n), const T, &var))\
	{\
		boost::fusion::fused<typename get_type<id>::value_type> functionObj (signal<id>()) ;\
		functionObj (boost::fusion::make_vector(BOOST_PP_ENUM_SHIFTED_PARAMS(BOOST_PP_INC(n), var))) ;\
	}

#define BOOST_PP_LOCAL_LIMITS (0, MAX_SIGNAL_PARAMS)
#include BOOST_PP_LOCAL_ITERATE()

	private:
		static MySignals* m_instance ;
		MySignals () 
        { 
			fusion::for_each(m_signals, initialize()) ;
        }
} ;

MySignals* MySignals :: m_instance = (MySignals *)0 ;

#if 0
void print_string (const string& p_string) 
{
	cout << "String Signal" << endl ;
	cout << p_string << endl ;
}

void print_data (const int& p_int, const string& p_string)
{
	cout << p_int << '-' << p_string << endl ;
	return ;
}

void print_void (void)
{
    cout << "Void Slot" << endl ;
    return ;
}
#endif

int main (void)
{
#if 0
	MySignals* sig = MySignals::instance() ;
    sig->signal<MySignals::VoidSignal>().connect(boost::lambda::bind(&print_void)) ;
    sig->signal<MySignals::StringSignal>().connect(boost::lambda::bind(&print_string, boost::lambda::_1)) ;
    sig->signal<MySignals::IntStringSignal>().connect(boost::lambda::bind(&print_data, boost::lambda::_1, boost::lambda::_2)) ;

	sig->emitSignal<MySignals::VoidSignal>() ;
	sig->emitSignal<MySignals::IntStringSignal>(4, "Surya") ;
#endif
}

