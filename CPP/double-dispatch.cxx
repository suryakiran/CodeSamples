#include <boost/mpl/vector.hpp>
#include <boost/mpl/for_each.hpp>
#include <boost/mpl/find_if.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/front.hpp>
#include <boost/mpl/next.hpp>
#include <boost/mpl/end.hpp>
#include <boost/mpl/iterator_range.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/current_function.hpp>
#include <boost/mpl/is_sequence.hpp>
#include <boost/mpl/list.hpp>
#include <boost/mpl/set.hpp>
#include <boost/mpl/sequence_tag.hpp>
#include <vector>
#include <typeinfo>
#include <boost/mpl/sequence_tag.hpp>
namespace mpl = boost::mpl;

#include <iostream>
using namespace std;

// The binding class hierarchy
struct Binding { virtual ~Binding() { } };
struct CurveBinding     : public Binding { };
struct MapBinding       : public Binding { };
struct PickBinding      : public Binding { };
struct AttributeBinding : public Binding { };

// The type interface class hierarcy
struct TypeInterface { virtual ~TypeInterface() { } };
struct NumericTypeInterface : public TypeInterface { };
struct BoolTypeInterface    : public TypeInterface { };
struct MapTypeInterface     : public TypeInterface { };

// The logic for double dispatch is taken from Modern C++ design from Andrei Alexandrescu
// Double dispatch - is a special form of multiple dispatch, and a mechanism that dispatches
// a function call to different concrete functions depending on the runtime types of two
// objects involved in the call
// First dynamic_cast the first argument to its most derived type and then dynamic_cast
// second argument to its most derived type and perform action on the derived types.

// Binding class types. The base class first and the list of
// derived classes, with most derived type appears at top of list

typedef mpl::vector<
  Binding
  , CurveBinding
  , MapBinding
  , PickBinding
  , AttributeBinding
  > BindingsList;

// Interface class types. 
typedef mpl::vector<
  TypeInterface
  , NumericTypeInterface
  , BoolTypeInterface
  , MapTypeInterface
  > TypesList;

// Dummy type to stop template instantiation
struct NullType { };

/********************************** Helper Classes *******************************
 * The helper classes are Car and Cdr
 * 
 * For a given sequence mpl::vector<type1, type2, type3, type4, type5> ...
 * 
 * CarSequence returns type1
 * CdrSequence returns mpl::iterator_range<type2, type3, type4, type5>
 *
 * For template instantiations where there's only one type in the sequence
 * mpl::vector<type1> or mpl::iterator_range<type1> ...
 *
 * CarSequence returns type1
 * CdrSequence returns NullType
 *
 * For template instantiations where the template arguments are not sequences,
 *
 * CarSequence returns NullType
 * CdrSequence returns NullType
 ******************************************************************************/

/************************ CAR Sequence *********************/
template <class Sequence, class SequenceTag>
struct CarSequence
{
  typedef typename mpl::front<Sequence>::type type;
};

//
// Partial Template specialization where the sequence tag is non_sequence_tag,
// Which means Sequence is not an mpl compatible sequence.
// 
template <class Sequence>
struct CarSequence<Sequence, mpl::non_sequence_tag>
{
  typedef NullType type;
};

//
// Partial Template specialization where the Sequence is NullType
// 

template <class SequenceTag>
struct CarSequence <NullType, SequenceTag>
{
  typedef NullType type;
};

/************************ CDR Sequence *********************/
template <class Sequence, class SequenceTag>
struct CdrSequence
{
  typedef typename mpl::next<typename mpl::begin<Sequence>::type>::type next_iterator;
  typedef typename mpl::end<Sequence>::type end_iterator;
  typedef typename boost::is_same <next_iterator, end_iterator>::type next_is_last;

  typedef typename mpl::eval_if < next_is_last,
                                  mpl::identity<NullType>,
                                  mpl::identity< mpl::iterator_range<next_iterator, end_iterator> >
                                  >::type type;
};

//
// Partial Template specialization where the sequence tag is non_sequence_tag,
// Which means Sequence is not an mpl compatible sequence.
// 

template <class Sequence>
struct CdrSequence <Sequence, mpl::non_sequence_tag>
{
  typedef NullType type;
};
/**************************************************************************************/
//
// Wrapper to get Car of sequence. Invokes appropriate template instantiation
// based on sequence_tag of Sequence
// 
template <class Sequence>
struct Car
{
  typedef typename mpl::sequence_tag<Sequence>::type tag;
  typedef typename CarSequence<Sequence, tag>::type type;
};

//
// Wrapper to get Cdr of sequence. Invokes appropriate template instantiation
// based on sequence_tag of Sequence
// 
template <class Sequence>
struct Cdr
{
  typedef typename mpl::sequence_tag<Sequence>::type tag;
  typedef typename CdrSequence<Sequence, tag>::type type;
};
/**************************************************************************************/

/************************ Dispatcher class *********************
 * Class Template.
 * First determines the dervied type of first kind by looping over all the types of first kind
 * If derived type of first kind is found
 *     do the same process for second kind by calling partial template specialization of Dispatcher
 *     with first types list set to NullType
 * If derived type of first kind is not found
 *     first type tail is NullType. Call dispatchFirstType from partial template specialization.
 *     This should handle the error situation.
 ****************************************************************/
 
template <class FirstTypeBase, class FirstTypesList, class SecondTypeBase, class SecondTypesList, class Executioner>
struct Dispatcher
{
  typedef typename Car<FirstTypesList>::type FirstTypeHead;
  typedef typename Cdr<FirstTypesList>::type FirstTypeTail;

  static Executioner dispatchFirstType(const FirstTypeBase* lhs, const SecondTypeBase* rhs, Executioner exec)
  {
    if(const FirstTypeHead* lh = dynamic_cast<const FirstTypeHead*>(lhs)) {
      return 
        Dispatcher<FirstTypeBase, NullType, SecondTypeBase, SecondTypesList, Executioner>::dispatchSecondType(lh, rhs, exec);
    } else {
      return
        Dispatcher<FirstTypeBase, FirstTypeTail, SecondTypeBase, SecondTypesList, Executioner>::dispatchFirstType(lhs, rhs, exec);
    }
  }
};

/*****************************************************************
 * Partial template specialization for Dispatcher.
 * With first derived type is already determined.
 *
 * Loop over list of types of second kind and determine the derived type of second kind
 * Once derived type of second kind is determined, Template specialization with list of types
 * of second kind set to NullType
 *****************************************************************/
 
template <class FirstTypeBase, class SecondTypeBase, class SecondTypesList, class Executioner>
struct Dispatcher<FirstTypeBase, NullType, SecondTypeBase, SecondTypesList, Executioner>
{
  typedef typename Car<SecondTypesList>::type SecondTypeHead;
  typedef typename Cdr<SecondTypesList>::type SecondTypeTail;

  //
  // Unable to determine the derived type of first kind. Error
  // 
  template <class DerivedFirstType>
  static Executioner dispatchFirstType(const DerivedFirstType*, const SecondTypeBase*, Executioner exec)
  {
    cout << "Error: " << endl;
    return exec;
  }

  //
  // Derived type of first kind is found.
  // Find out derived type of second kind
  // 
  template <class DerivedFirstType>
  static Executioner dispatchSecondType(const DerivedFirstType* lhs, const SecondTypeBase* rhs, Executioner exec)
  {
    if(const SecondTypeHead* rh = dynamic_cast<const SecondTypeHead*>(rhs)) {
      return
        Dispatcher<FirstTypeBase, NullType, SecondTypeBase, NullType, Executioner>::execute(lhs, rh, exec);
    } else {
      return
        Dispatcher<FirstTypeBase, NullType, SecondTypeBase, SecondTypeTail, Executioner>::dispatchSecondType(lhs, rhs, exec);
    }
  }
};

/**********************************************************************************
 * All the first and second types are exhausted. If derived type of second kind is
 * still not found, then its an error. Otherwise, call execute.
 * Executioner takes derived types of first and second arguments and calls one of
 * different permutations of overloads of operator() in Executioner
 *********************************************************************************/
 
template <class FirstTypeBase, class SecondTypeBase, class Executioner>
struct Dispatcher<FirstTypeBase, NullType, SecondTypeBase, NullType, Executioner>
{
  template <class DerivedFirstType, class DerivedSecondType>
  static Executioner dispatchSecondType(const DerivedFirstType* lhs, const DerivedSecondType* rhs, Executioner exec)
  {
    cout << "Error in dispatching second argument" << endl;
    return exec;
  }

  template <class DerivedFirstType, class DerivedSecondType>
  static Executioner execute(const DerivedFirstType* lhs, const DerivedSecondType* rhs, Executioner exec)
  {
    exec(lhs, rhs);
    return exec;
  }
};

template <class FirstTypeList, class SecondTypeList, class Executioner>
struct DoubleDispatch
{
  // First argument base type
  typedef typename Car<FirstTypeList>::type FirstBaseType;
  
  // Second argument basetype.
  typedef typename Car<SecondTypeList>::type SecondBaseType;

  // DerivedTypesList of first argument
  typedef typename::Cdr<FirstTypeList>::type DTLFirstType;
  
  // DerivedTypesList of second argument
  typedef typename::Cdr<SecondTypeList>::type DTLSecondType;

  static Executioner dispatch(const FirstBaseType* lhs, const SecondBaseType* rhs, Executioner exec)
  {
    return
      Dispatcher<FirstBaseType, DTLFirstType, SecondBaseType, DTLSecondType, Executioner>::dispatchFirstType(lhs, rhs, exec);
  }
};

// Function to perform action on the derived types. operator() is overloaded for all the
// combinations of type derivations.

struct DoubleDispatchFunction
{
  void operator()(const Binding*, const TypeInterface*)
  {
    cout << BOOST_CURRENT_FUNCTION << endl;
  }

  void operator()(const CurveBinding*, const NumericTypeInterface*)
  {
    cout << BOOST_CURRENT_FUNCTION << endl;
  }

  void operator()(const CurveBinding*, const BoolTypeInterface*)
  {
    cout << BOOST_CURRENT_FUNCTION << endl;
  }

  void operator()(const CurveBinding*, const MapTypeInterface*)
  {
    cout << BOOST_CURRENT_FUNCTION << endl;
  }

  void operator()(const MapBinding*, const NumericTypeInterface*)
  {
    cout << BOOST_CURRENT_FUNCTION << endl;
  }

  void operator()(const MapBinding*, const BoolTypeInterface*)
  {
    cout << BOOST_CURRENT_FUNCTION << endl;
  }

  void operator()(const MapBinding*, const MapTypeInterface*)
  {
    cout << BOOST_CURRENT_FUNCTION << endl;
  }

  void operator()(const PickBinding*, const NumericTypeInterface*)
  {
    cout << BOOST_CURRENT_FUNCTION << endl;
  }

  void operator()(const PickBinding*, const BoolTypeInterface*)
  {
    cout << BOOST_CURRENT_FUNCTION << endl;
  }

  void operator()(const PickBinding*, const MapTypeInterface*)
  {
    cout << BOOST_CURRENT_FUNCTION << endl;
  }

  void operator()(const AttributeBinding*, const NumericTypeInterface*)
  {
    cout << BOOST_CURRENT_FUNCTION << endl;
  }

  void operator()(const AttributeBinding*, const BoolTypeInterface*)
  {
    cout << BOOST_CURRENT_FUNCTION << endl;
  }

  void operator()(const AttributeBinding*, const MapTypeInterface*)
  {
    cout << BOOST_CURRENT_FUNCTION << endl;
  }

};

int main (void)
{
  Binding* binding = new AttributeBinding();
  TypeInterface* typeInterface = new BoolTypeInterface();
  DoubleDispatchFunction ddf;
  ddf = DoubleDispatch<BindingsList,TypesList,DoubleDispatchFunction>::dispatch(binding, typeInterface, ddf);
}
