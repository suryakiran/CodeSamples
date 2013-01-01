#include "std.hxx"

struct Test
{
  Test()
  {
    cout << "Test Constructor" << endl;
  }

  template <class T>
    T func ()
    {
      cout << typeid(T).name() << endl;
      return T();
    }
};

template <class T>
void freeFun(T arg)
{
  arg.template func<string>();
}

int main (void)
{
  Test t;
  freeFun (t);
}
