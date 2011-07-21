#include <Derived.h>
#include <iostream>
using namespace std;

Derived::Derived()
  : Base(), m_d (19.5)
{
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
}

void
Derived::virtualFun ()
{
  cout << "Virtual Function in Derived" << endl;
}
