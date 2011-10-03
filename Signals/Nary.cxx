#include <iostream>
#include <algorithm>
#include <typeinfo>
using namespace std;

#include <Signals/BoostSlots.hxx>
#include <Signals/SignalBase.hxx>

#include <boost/typeof/typeof.hpp>

#include <boost/function_types/function_arity.hpp>
#include <boost/function_types/function_type.hpp>
#include <boost/function_types/parameter_types.hpp>
namespace bfun = boost::function_types;

#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/add_pointer.hpp>

#define SLOT(class,func,obj)\
  MEM_FUN_OBJ_PTR(class,func,obj,0)

template <class SlotClass, class Func, int NumArgs>
struct slot
{
  slot(SlotClass* p_slotObj)
  {
  }

  slot (SlotClass& p_slotObj)
  {
  }
  private:
    SlotClass* m_slot;
    Func m_func;
};

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

struct MySlot 
{
  MySlot() { }

  virtual void voidSlot () { cout << "MySlot::voidSlot" << endl; }
  virtual void argSlot(int) { }
};

struct MySlotDerived : public MySlot
{
  MySlotDerived() { 
    cout << "MySlot Derived" << endl;
  }

  virtual void voidSlot () { cout << "MySlotDerived::voidSlot" << endl; }
};

int main (void)
{
  cout << "--------------------------------" << endl;

  Signal sig;
  MySlot* slot = new MySlotDerived();
  sig.signal<signal::id::VoidSignal>().connect(MEM_FUN_OBJ_PTR (MySlot,voidSlot,slot,0));
  //sig.signal<signal::id::VoidSignal>().connect(SLOT(MySlot, voidSlot, slot));
  sig.emitSignal<signal::id::VoidSignal>();

  cout << "--------------------------------" << endl;
}
