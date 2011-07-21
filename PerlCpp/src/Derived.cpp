#include <Derived.h>
#include <iostream>
using namespace std;

Derived::Derived()
  : Base(), m_d (19.5)
{
  cout << "Derived Constructor" << endl;
  m_s = "Derived";
}

void
Derived::setDouble (const double& p_d)
{
  m_d = p_d;
}

const double&
Derived::getDouble (void) const
{
  return m_d;
}

Derived::~Derived()
{
  cout << "Derived Destructor" << endl;
}

void
Derived::virtualFun ()
{
  cout << "Virtual Function in Derived" << endl;
}
