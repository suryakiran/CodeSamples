#include <iostream>
#include <algorithm>
#include <typeinfo>
using namespace std;

#include <Signals/BoostSlots.hxx>
#include <Signals/Signals.hxx>

#include <boost/typeof/typeof.hpp>

#include <boost/function_types/function_arity.hpp>
#include <boost/function_types/function_type.hpp>
#include <boost/function_types/parameter_types.hpp>
namespace bfun = boost::function_types;

#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/add_pointer.hpp>

class Signal;

namespace signal {
  namespace id {
    struct VoidSignal;
  }

  template <>
    struct types <Signal> 
    {
      typedef fusion::map <
        fusion::pair <id::VoidSignal, BOOST_SIGNAL(void())>
        > type;
    };
}

class Signal : public SignalBase <Signal>
{
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
    cout << "Slot Derived" << endl;
  }

  virtual void voidSlot () { cout << "SlotDerived::voidSlot" << endl; }
};

int main (void)
{
  cout << "--------------------------------" << endl;

  Signal sig;
  Slot* slot = new SlotDerived();
  sig.signal<signal::id::VoidSignal>().connect(MEM_FUN_OBJ_PTR (Slot,voidSlot,slot,0));
  sig.emitSignal<signal::id::VoidSignal>();

  cout << "--------------------------------" << endl;
}
