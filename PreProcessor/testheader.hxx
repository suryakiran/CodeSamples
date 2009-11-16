#ifndef TEST_HEADER_HXX
#define TEST_HEADER_HXX 1

#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/control/expr_if.hpp>
#include <boost/preprocessor/control/if.hpp>
#include <boost/preprocessor/facilities/empty.hpp>
#include <boost/preprocessor/punctuation/comma.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>

#include <boost/lambda/lambda.hpp>
#include <boost/lambda/bind.hpp>

#define BOOST_SLOT(klass, func, sendObj, obj, isReference, numArgs) \
	boost::lambda::bind (&klass::func \
			BOOST_PP_EXPR_IF (sendObj, \
				BOOST_PP_COMMA() BOOST_PP_IF(isReference, ref(obj), obj)) \
			BOOST_PP_IF (numArgs, BOOST_PP_COMMA, BOOST_PP_EMPTY)() \
			BOOST_PP_IF (numArgs, BOOST_PP_ENUM_SHIFTED_PARAMS, BOOST_PP_TUPLE_EAT(2))\
			(BOOST_PP_INC(numArgs), boost::lambda::_))

#define MEM_FUN_OBJ_PTR(klass, func, obj, numArgs)\
	BOOST_SLOT(klass, func, 1, obj, 0, numArgs)

#define MEM_FUN_OBJ_REF(klass, func, obj, numArgs)\
	BOOST_SLOT(klass, func, 1, obj, 1, numArgs)

#define MEM_FUN(klass, func, numArgs)\
	MEM_FUN_OBJ_PTR(klass, func, this, numArgs)

#define PTR_FUN(klass, func, numArgs)\
	BOOST_SLOT(klass, func, 0, nil, 0, numArgs)

#define MEM_FUN_REF(klass, func, numArgs)\
	MEM_FUN_OBJ_REF(klass, func, this, numArgs)

template<BOOST_PP_ENUM_PARAMS(NUM,typename T)>
struct skg 
{
	MEM_FUN(skg, print_data, 3) ;
	PTR_FUN(skg, print_data, 0) ;
	MEM_FUN_OBJ_REF(skg, print_data, ting, 2) ;
} ;

#endif
