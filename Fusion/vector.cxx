#include <iostream>
#include <string>
using namespace std ;

#include <boost/signals2.hpp>
#include <boost/typeof/typeof.hpp>

#include <boost/fusion/container.hpp>
#include <boost/fusion/sequence/intrinsic.hpp>
#include <boost/fusion/functional/invocation/invoke.hpp>
#include <boost/fusion/functional.hpp>
#include <boost/fusion/include/for_each.hpp>
#include <boost/utility/value_init.hpp>

#include <boost/lambda/lambda.hpp>
#include <boost/lambda/bind.hpp>

using boost::shared_ptr ;
using namespace boost ;

#define MAX_SIGNAL_PARAMS 10
#define SIGNAL_ARGS       boost::fusion::make_vector
#define SignalArgsVec     boost::fusion::vector <BOOST_PP_ENUM_PARAMS(MAX_SIGNAL_PARAMS, T)>

#define BOOST_SIGNAL(...) boost::shared_ptr< boost::signals2::signal < __VA_ARGS__ > >

class MySignals
{
	private:
		typedef boost::fusion::vector <
            BOOST_SIGNAL(void(const int&, const string&))
            , BOOST_SIGNAL(void())
            , BOOST_SIGNAL(void(const string&))
            > SignalsVec ;

		SignalsVec m_signals ;

        struct initialize
        {
            template <typename T>
                void operator() (T& p_item) const
                {
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
		typename fusion::result_of::at_c<SignalsVec, id>::type 
			signal (void) { return fusion::at_c<id>(m_signals) ; }

	template <int id, BOOST_PP_ENUM_PARAMS(MAX_SIGNAL_PARAMS, typename T)>        
		void emitSignal (const SignalArgsVec& p_vector)                           
			{                                                                     
				fusion::fused <typename fusion::result_of::at_c<SignalsVec, id>::type>     
				functionObj (signal <id>()) ;                                     
				functionObj (p_vector) ;                                          
			}                                                                     
                                                                                  
	template<int id>                                                              
		void emitSignal (void)                                                    
			{                                                                     
				emitSignal<id> (SIGNAL_ARGS()) ;                                  
			}

	private:
		static MySignals* m_instance ;
		MySignals () 
        { 
            //fusion::at_c<VoidSignal>(m_signals) = new signal<void()>() ;
            fusion::at_c<IntStringSignal>(m_signals) = new signal<void(const int&, const string&)>() ;
            //fusion::at_c<StringSignal>(m_signals) = new signal<void(const string&)>() ;
        }
} ;

MySignals* MySignals :: m_instance = (MySignals *)0 ;

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

int main (void)
{
	MySignals* sig = MySignals::instance() ;
#if 0
    sig->signal<MySignals::VoidSignal>()->connect(boost::lambda::bind(&print_void)) ;
#endif
}
