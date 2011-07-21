#include <Base.h>
#include <iostream>
using namespace std;

Base::Base()
  : m_i (19), m_s("Base"), name("Accessor Name"), boolVar(true)
{
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
}

void
Base::printThis (const Base* p_basePtr)
{
  cout << p_basePtr->getString() << endl;
}

void
Base::addItem (const string& p_s)
{
  m_vs.push_back(p_s);
}
