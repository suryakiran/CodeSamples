#include "std.hxx"

#include <boost/typeof/typeof.hpp>
// #include <boost-spirit.hxx>

#include <boost/fusion/container.hpp>
#include <boost/fusion/sequence/intrinsic.hpp>
#include <boost/fusion/include/for_each.hpp>
#include <boost/fusion/functional/invocation/invoke.hpp>
#include <boost/fusion/functional.hpp>
namespace fusion = boost::fusion;

#include <boost/shared_ptr.hpp>

#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/type_traits/add_reference.hpp>

#include <boost/preprocessor/repetition/enum_shifted_binary_params.hpp>

#include <boost/signals2.hpp>
namespace signals = boost::signals2 ;
#define BOOST_SIGNAL(...) boost::shared_ptr< signals::signal < __VA_ARGS__ > >

#define DEF_STRUCT(name) struct name { }

#ifndef MAX_SIGNAL_PARAMS
#define MAX_SIGNAL_PARAMS 10
#endif

namespace detail {
  template <class Class>
  struct has_typedef
  {
    typedef char yes[1];
    typedef char no[2];
    
    template <class T>
    static yes& test(typename T::element_type*);
    
    template <class T>
    static no& test(...);
    static const bool value = sizeof(test<Class>(0)) == sizeof(yes);
  };

  template <class SmartPtrType, bool b>
  struct element_type_p {
    typedef typename SmartPtrType::element_type value_type;
    typedef typename boost::add_reference<value_type>::type reference_type;
  };

  template <class SmartPtrType>
  struct element_type_p<SmartPtrType, false> {
    typedef typename SmartPtrType::value_type value_type;
    typedef typename SmartPtrType::reference_type reference_type;
  };
  
  template <class SmartPtrType>
  struct element_type {
    static const bool value = has_typedef<SmartPtrType>::value;
    typedef typename element_type_p<SmartPtrType, value>::value_type value_type;
    typedef typename element_type_p<SmartPtrType, value>::reference_type reference_type;
  };
}

class SigClass
{
	public:
		DEF_STRUCT(VoidSignal);
		DEF_STRUCT(IntSignal);
		DEF_STRUCT(StringSignal);

	private:
		typedef fusion::map <
				fusion::pair <VoidSignal,   BOOST_SIGNAL(void()) >
			,	fusion::pair <IntSignal,    BOOST_SIGNAL(void(int)) >
			,	fusion::pair <StringSignal, BOOST_SIGNAL(void(string)) >
			> FusionMap;

		FusionMap fm ;

		bool m_blockAllSignals;

	private:
		template <class T>
			struct get_type
			{
				typedef typename boost::remove_reference <
					typename fusion::result_of::at_key<FusionMap, T>::type>::type smart_ptr_type;
        typedef typename detail::element_type<smart_ptr_type>::reference_type reference_type;
			} ;

		struct initialize 
		{
			template <typename FusionMapItem>
				void operator() (FusionMapItem& p_item) const
				{
					typedef typename FusionMapItem::second_type SmartPtr;
          typedef typename detail::element_type<SmartPtr>::value_type ItemType;
					p_item.second = SmartPtr(new ItemType) ;
				}
		} ;

	public:
		SigClass ()
			: m_blockAllSignals (false)
		{ fusion::for_each (fm, initialize()) ; }

		void blockAllSignals (bool b) { m_blockAllSignals = b; }
		bool blockAllSignals (void) const { return m_blockAllSignals ; }

		template <class T> 
			typename get_type<T>::reference_type
				signal (void)
				{
					return *(fusion::at_key<T>(fm));
				}

#define BOOST_PP_LOCAL_MACRO(n)\
	template<class id BOOST_PP_COMMA_IF(n) BOOST_PP_ENUM_SHIFTED_PARAMS(BOOST_PP_INC(n), typename T)> \
	void emitSignal(\
            BOOST_PP_IF(n, BOOST_PP_ENUM_SHIFTED_BINARY_PARAMS, void BOOST_PP_TUPLE_EAT(3))\
            (BOOST_PP_INC(n), const T, &var))\
	{\
		boost::fusion::fused<typename get_type<id>::reference_type> functionObj (signal<id>()) ; \
		if (blockAllSignals()) return ;\
		functionObj (boost::fusion::make_vector(BOOST_PP_ENUM_SHIFTED_PARAMS(BOOST_PP_INC(n), var))) ;\
	}

#define BOOST_PP_LOCAL_LIMITS (0, MAX_SIGNAL_PARAMS)
#include BOOST_PP_LOCAL_ITERATE()
} ;

void IntSlot (int i)
{
	cout << "Int Slot\n\tValue: " << i << endl ;
}

void VoidSlot (void)
{
	cout << "Void Slot\n\tValue: Nothing" << endl ;
}

void StringSlot (string s)
{
	cout << "String Slot\n\tValue: " << s << endl ;
}

int main (void)
{
	cout << "============== Fusion Maps Test ==============" << endl ;

	SigClass sc ;
	sc.signal<SigClass::VoidSignal>().connect (phx::bind(&VoidSlot));
	sc.signal<SigClass::IntSignal>().connect (phx::bind(&IntSlot, pha::arg1));
	sc.signal<SigClass::StringSignal>().connect (phx::bind(&StringSlot, pha::arg1));

	sc.blockAllSignals(false);

	// sc.blockSignal<SigClass::VoidSignal> (true);

	sc.emitSignal<SigClass::VoidSignal>();
	sc.emitSignal<SigClass::IntSignal>(5);
	sc.emitSignal<SigClass::StringSignal>("Surya Kiran");
}
