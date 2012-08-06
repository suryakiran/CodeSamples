#include <std.hxx>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/for_each.hpp>
#include <boost/mpl/find_if.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/current_function.hpp>
namespace mpl = boost::mpl;

struct Binding { virtual ~Binding() { } };
struct CurveBinding     : public Binding { };
struct MapBinding       : public Binding { };
struct PickBinding      : public Binding { };
struct AttributeBinding : public Binding { };
struct SkgBinding       : public Binding { };

struct TypeInterface { virtual ~TypeInterface() { } };
struct NumericTypeInterface : public TypeInterface { };
struct BoolTypeInterface    : public TypeInterface { };
struct MapTypeInterface     : public TypeInterface { };

typedef mpl::vector<
  Binding
  , CurveBinding
  , MapBinding
  , PickBinding
  , AttributeBinding
  , SkgBinding
  > BindingsList;

typedef mpl::vector<
  TypeInterface
  , NumericTypeInterface
  , BoolTypeInterface
  , MapTypeInterface
  > TypesList;

struct null_type { };

template <class Types>
struct head_and_tail
{
  typedef typename mpl::front<Types>::type head;
  typedef typename mpl::next<typename mpl::begin<Types>::type>::type next_item;
  typedef typename mpl::end<Types>::type last;
  typedef typename boost::is_same <next_item, last>::type next_is_last;
  typedef typename mpl::if_ < next_is_last,
                              null_type,
                              mpl::iterator_range<next_item, last>
                              >::type tail;
};

template <>
struct head_and_tail<null_type>
{
  typedef null_type head;
  typedef null_type tail;
};

template <class BaseTypeLhs, class TypesLhs, class BaseTypeRhs, class TypesRhs, class Executioner>
struct Dispatcher
{
  typedef typename head_and_tail<TypesLhs>::head lhs_head;
  typedef typename head_and_tail<TypesLhs>::tail lhs_tail;

  static void dispatch_lhs(const BaseTypeLhs* lhs, const BaseTypeRhs* rhs)
  {
    if(const lhs_head* lh = dynamic_cast<const lhs_head*>(lhs)) {
      Dispatcher<BaseTypeLhs, null_type, BaseTypeRhs, TypesRhs, Executioner>::dispatch_rhs(lh, rhs);
    } else {
      Dispatcher<BaseTypeLhs, lhs_tail, BaseTypeRhs, TypesRhs, Executioner>::dispatch_lhs(lhs, rhs);
    }
  }
};

template <class BaseTypeLhs, class BaseTypeRhs, class TypesRhs, class Executioner>
struct Dispatcher<BaseTypeLhs, null_type, BaseTypeRhs, TypesRhs, Executioner>
{
  typedef typename head_and_tail<TypesRhs>::head rhs_head;
  typedef typename head_and_tail<TypesRhs>::tail rhs_tail;

  template <class SomeLhs>
  static void dispatch_lhs(const SomeLhs*, const BaseTypeRhs*)
  {
    cout << "Error: " << endl;
  }

  template <class SomeLhs>
  static void dispatch_rhs(const SomeLhs* lhs, const BaseTypeRhs* rhs)
  {
    if(const rhs_head* rh = dynamic_cast<const rhs_head*>(rhs)) {
      Dispatcher<BaseTypeLhs, null_type, BaseTypeRhs, null_type, Executioner>::execute(lhs, rh);
    } else {
      Dispatcher<BaseTypeLhs, null_type, BaseTypeRhs, rhs_tail, Executioner>::dispatch_rhs(lhs, rhs);
    }
  }
};

template <class BaseTypeLhs, class BaseTypeRhs, class Executioner>
struct Dispatcher<BaseTypeLhs, null_type, BaseTypeRhs, null_type, Executioner>
{
  template <class SomeLhs, class SomeRhs>
  static void dispatch_rhs(const SomeLhs* lhs, const SomeRhs* rhs)
  {
    cout << "Error in dispatching second argument" << endl;
  }

  template <class SomeLhs, class SomeRhs>
  static void execute(const SomeLhs* lhs, const SomeRhs* rhs)
  {
    Executioner exec;
    exec(lhs, rhs);
  }
};

template <class TypeLhs, class TypeRhs, class Executioner>
struct DoubleDispatch
{
  typedef typename mpl::front<TypeLhs>::type lhs_base_type;
  typedef typename mpl::front<TypeRhs>::type rhs_base_type;
  typedef Executioner(*Callback)(const lhs_base_type*, const rhs_base_type*);

  typedef typename mpl::next<typename mpl::begin<TypeLhs>::type>::type lhs_derived_types_begin;
  typedef typename mpl::next<typename mpl::begin<TypeRhs>::type>::type rhs_derived_types_begin;

  typedef typename mpl::end<TypeLhs>::type lhs_end;
  typedef typename mpl::end<TypeRhs>::type rhs_end;

  typedef typename mpl::iterator_range<lhs_derived_types_begin, lhs_end>::type lhs_range;
  typedef typename mpl::iterator_range<rhs_derived_types_begin, rhs_end>::type rhs_range;

  static void dispatch(const lhs_base_type* lhs, const rhs_base_type* rhs)
  {
    Dispatcher<lhs_base_type, lhs_range, rhs_base_type, rhs_range, Executioner>::dispatch_lhs(lhs, rhs);
  }
};

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
  Binding* cb = new SkgBinding();
  TypeInterface* nt = new BoolTypeInterface();
  DoubleDispatch<BindingsList,TypesList,DoubleDispatchFunction>::dispatch(cb, nt);
}
