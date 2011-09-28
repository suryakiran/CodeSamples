#include <iostream>
#include <algorithm>
#include <Signals/Signals.hxx>
#include <Signals/BoostSlots.hxx>
#include <boost/typeof/typeof.hpp>
#include <boost/function_types/function_arity.hpp>
#include <boost/function_types/function_type.hpp>
#include <boost/function_types/parameter_types.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/add_pointer.hpp>
using namespace std;
namespace bfun = boost::function_types;

class Signal : public SignalBase
{
  public:
    struct VoidSignal;

    typedef fusion::map <
      fusion::pair <VoidSignal, BOOST_SIGNAL(void())>
      > SignalsMap;
#include <Signals/SignalMacros.hxx>

  public:
    Signal() { 
      fusion::for_each(m_signals, initialize());
    }
};

struct Slot 
{
  Slot() { }

  virtual void voidSlot () { cout << "Slot::voidSlot" << endl; }
  virtual void argSlot(int) { }
};

struct SlotDerived : public Slot
{
  SlotDerived() { 
    cout << typeid (BOOST_TYPEOF(this)).name() << endl;
  }

  virtual void voidSlot () { cout << "SlotDerived::voidSlot" << endl; }
};

int main (void)
{
  cout << "--------------------------------" << endl;

  Signal sig;
  Slot* slot = new SlotDerived();
  sig.signal<Signal::VoidSignal>().connect(MEM_FUN_OBJ_PTR (Slot,voidSlot,slot,0));

  sig.emitSignal<Signal::VoidSignal>();
  typedef BOOST_TYPEOF (slot) slotType;
  cout << typeid(slotType).name() << endl;
  typedef BOOST_TYPEOF (&Slot::argSlot) funcType;
  cout << bfun::function_arity<funcType>::value << endl;
  typedef boost::mpl::at_c<bfun::parameter_types<funcType>, 0>::type arg0Type;
  typedef boost::add_pointer<arg0Type>::type arg0pType;
  cout << boost::is_same<arg0pType, slotType>::value << endl;

  cout << "--------------------------------" << endl;
}
