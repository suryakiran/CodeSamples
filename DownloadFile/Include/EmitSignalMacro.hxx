//
// Not putting this piece of code between ifdef guards as this needs to be
// included as and when asked for.
//

#include <boost/preprocessor/control/expr_if.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/iteration/local.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/repetition/enum_shifted_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_shifted_params.hpp>

#ifndef MAX_SIGNAL_PARAMS
#define MAX_SIGNAL_PARAMS 10
#endif 

#define BOOST_PP_LOCAL_MACRO(n)\
	template<int id BOOST_PP_COMMA_IF(n) BOOST_PP_ENUM_SHIFTED_PARAMS(BOOST_PP_INC(n), typename T)> \
	void emitSignal(BOOST_PP_IF(n,BOOST_PP_ENUM_SHIFTED_BINARY_PARAMS,void BOOST_PP_TUPLE_EAT(3))\
			(BOOST_PP_INC(n), const T, &var))\
	{\
		boost::fusion::fused<typename get_type<id>::value_type> functionObj (signal<id>()) ;\
		if (blockSignals() || blockSignal(id)) return ;\
		functionObj (boost::fusion::make_vector(BOOST_PP_ENUM_SHIFTED_PARAMS(BOOST_PP_INC(n), var))) ;\
	}

#define BOOST_PP_LOCAL_LIMITS (0, MAX_SIGNAL_PARAMS)
#include BOOST_PP_LOCAL_ITERATE()
