#include <Example.h>
#include <iostream>
using namespace std;

Example::Example()
  : m_i (19), m_s("Surya Kiran")
{
  cout << "Example Constructor" << endl;
}

void
Example::setInt (const int& p_i)
{
  m_i = p_i;
}

const int&
Example::getInt (void) const
{
  return m_i;
}

void
Example::setString (const string& p_s)
{
  m_s = p_s;
}

const string&
Example::getString (void) const
{
  return m_s;
}

Example::~Example()
{
    cout << "Example Destructor" << endl;
}
