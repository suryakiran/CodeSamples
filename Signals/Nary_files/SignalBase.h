#ifndef SignalBase_h_INCLUDED
#define SignalBase_h_INCLUDED 1

#include <signal_types.h>

#include <boost/type_traits/remove_reference.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/signals2.hpp>

#define BOOST_SIGNAL(...) boost::shared_ptr< boost::signals2::signal < __VA_ARGS__ > >

#include <boost/preprocessor/control/expr_if.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/iteration/local.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/repetition/enum_shifted_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_shifted_params.hpp>

#ifndef MAX_SIGNAL_PARAMS
#define MAX_SIGNAL_PARAMS 10
#endif 

template <class derived_class>
class SignalBase
{
  public:
    typedef typename signal::types<derived_class>::type signal_type;
    typedef SignalBase<derived_class> base_type;

  private:
    template<class T> 
      struct get_type                                                   
      {                                                                                  
        typedef typename boost::remove_reference <
          typename fusion::result_of::at_key<signal_type, T>::type>::type
          ::reference value_type;
      };                                                                                

    struct initialize                                                                  
    {                                                                                  
      template <typename FusionMapItem>
        void operator() (FusionMapItem& p_item) const
        {
          typedef typename FusionMapItem::second_type SmartPtr;
          typedef typename SmartPtr::value_type ItemType ;
          p_item.second = SmartPtr(new ItemType) ;
        }
    };                                                                               

  public:
    SignalBase()
      :m_blockSignals(false)
    {
      fusion::for_each (m_signals, initialize());
    }

    template <class T>                                                                  
      typename get_type<T>::value_type                                              
      signal (void) { return *(fusion::at_key<T>(m_signals)) ; }           

    virtual ~SignalBase()
    {
    }

		bool blockSignals (void)   { return m_blockSignals ; }
		void blockSignals (bool b) { m_blockSignals = b ; }

#define BOOST_PP_LOCAL_MACRO(n)\
	template<class id BOOST_PP_COMMA_IF(n) BOOST_PP_ENUM_SHIFTED_PARAMS(BOOST_PP_INC(n), typename T)> \
	void emitSignal(BOOST_PP_IF(n,BOOST_PP_ENUM_SHIFTED_BINARY_PARAMS,void BOOST_PP_TUPLE_EAT(3))\
			(BOOST_PP_INC(n), const T, &var))\
	{\
		fusion::fused<typename get_type<id>::value_type> functionObj (signal<id>()) ;\
		if (blockSignals()) return ;\
		functionObj (fusion::make_vector(BOOST_PP_ENUM_SHIFTED_PARAMS(BOOST_PP_INC(n), var))) ;\
	}

#define BOOST_PP_LOCAL_LIMITS (0, MAX_SIGNAL_PARAMS)
#include BOOST_PP_LOCAL_ITERATE()

  protected:
    signal_type m_signals;

  private:
		bool m_blockSignals ;
};

#endif
