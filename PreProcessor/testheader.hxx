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

#define NUM 5

#define PP_ARG_N(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,_21,_22,_23,_24,_25,_26,_27,_28,_29,_30,_31,_32,_33,_34,_35,_36,_37,_38,_39,_40,_41,_42,_43,_44,_45,_46,_47,_48,_49,_50,_51,_52,_53,_54,_55,_56,_57,_58,_59,_60,_61,_62,_63,N,...) N 

#define PP_RSEQ_N()63,62,61,60,59,58,57,56,55,54,53,52,51,50,49,48,47,46,45,44,43,42,41,40,39,38,37,36,35,34,33,32,31,30,29,28,27,26,25,24,23,22,21,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0

#define PP_NARG_(...) PP_ARG_N(__VA_ARGS__)

#define PP_NARG(...) PP_NARG_(__VA_ARGS__,PP_RSEQ_N())

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

#define MEM_FUN(klass, func, ...)\
	MEM_FUN_OBJ_PTR(klass, func, this, ##__VA_ARGS__)

#define PTR_FUN(klass, func, numArgs)\
	BOOST_SLOT(klass, func, 0, nil, 0, numArgs)

#define MEM_FUN_REF(klass, func, numArgs)\
	MEM_FUN_OBJ_REF(klass, func, this, numArgs)

template<BOOST_PP_ENUM_PARAMS(NUM,typename T)>
struct skg 
{
	PP_ARG_N(10,20,63,62,61,60,59,58,57,56,55,54,53,52,51,50,49,48,47,46,45,44,43,42,41,40,39,38,37,36,35,34,33,32,31,30,29,28,27,26,25,24,23,22,21,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0) ;
	PP_ARG_N(10,20,PP_RSEQ_N())
//	cout << "Number of arguments: " << PP_NARG(skg,kiran) << endl ;
} ;

#endif
