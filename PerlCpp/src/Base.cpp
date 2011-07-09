#include <Base.h>
#include <iostream>
using namespace std;

Base::Base()
  : m_i (19), m_s("Surya Kiran"), name("Accessor Name"), boolVar(true)
{
  cout << "Base Constructor" << endl;
  StringVec& vec = stringVecVar();
  vec.push_back ("Vector Item: 1");
  vec.push_back ("Vector Item: 2");
  vec.push_back ("Vector Item: 3");
}

void
Base::setInt (const int& p_i)
{
  m_i = p_i;
}

const int&
Base::getInt (void) const
{
  return m_i;
}

void
Base::setString (const string& p_s)
{
  m_s = p_s;
}

const string&
Base::getString (void) const
{
  return m_s;
}

Base::~Base()
{
    cout << "Base Destructor" << endl;
}
