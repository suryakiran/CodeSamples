#include <iostream>
#include <string>
using namespace std ;

#include <boost/typeof/typeof.hpp>

#include <boost/fusion/container.hpp>
#include <boost/fusion/sequence/intrinsic.hpp>
#include <boost/fusion/functional/invocation/invoke.hpp>
#include <boost/fusion/functional.hpp>
#include <boost/fusion/include/for_each.hpp>
#include <boost/utility/value_init.hpp>

#include <boost/format.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/lambda/bind.hpp>

using boost::shared_ptr ;
using boost::format ;
using namespace boost ;

#define BOOST_SIGNAL(...) boost::shared_ptr< boost::signals2::signal < __VA_ARGS__ > >
#define PTR(...) boost::shared_ptr< __VA_ARGS__ >

class MySignals
{
	private:
		typedef boost::fusion::vector <
			PTR(int), PTR(float), PTR(double)
			> Vector ;

		Vector m_vec ;

		template<int id>
			void init ()
			{
				typedef typename fusion::result_of::at_c<Vector, id>::type ItemType ;
				typedef typename fusion::result_of::at_c<Vector, id>::type::value_type ValueType ;

				fusion::at_c<id>(m_vec) = new ValueType ;
			}

        struct Initialize
        {
            template <typename T>
                void operator() (T& p_item) const
                {
					typedef typename T::value_type ArgType ;
	//				typedef typename fusion::result_of::at_c<Vector, 1>::type ItemType ;

					if (typeid(ArgType) == typeid(int))
						p_item = T(new ArgType(5)) ;

					if (typeid(ArgType) == typeid(float))
						p_item = T(new ArgType(10.0)) ;

					if (typeid(ArgType) == typeid(double))
						p_item = T(new ArgType(15.2)) ;
#if 0
					cout << format("Arg Type is %1%, Item Type is %2%")
						% typeid(ArgType).name() % typeid(ItemType).name()
						<< endl ;
#endif
                }

        } ;

		struct Print
		{
			template <typename T>
				void operator() (T& p_item) const
				{
					cout << "Value is: " << *p_item << endl ;
				}
		} ;

	public:
		static MySignals* instance (void) 
		{ 
			if (!m_instance) 
				m_instance = new MySignals ;
			return m_instance ; 
		}

#if 0
		enum {
			Zero = 0,
			One,
			Two
		} ;
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
#endif

	private:
		static MySignals* m_instance ;
		MySignals () 
        { 
		//	init<0>() ;
			fusion::for_each(m_vec, Initialize()) ;
			fusion::for_each(m_vec, Print()) ;
            //fusion::at_c<VoidSignal>(m_vec) = new signal<void()>() ;
            //fusion::at_c<IntStringSignal>(m_vec) = new signal<void(const int&, const string&)>() ;
            //fusion::at_c<StringSignal>(m_vec) = new signal<void(const string&)>() ;
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
	MySignals* sig = MySignals::instance() ;
#if 0
    sig->signal<MySignals::VoidSignal>()->connect(boost::lambda::bind(&print_void)) ;
#endif
}
