#include <boost/mpl/map.hpp>
#include <boost/mpl/at.hpp>
#include <iostream>
using namespace std;

namespace mpl = boost::mpl;

struct Test
{
  Test() { }
  virtual void printValue() const = 0;
};

struct TestInt : public Test
{
  TestInt(int val): m_val(val) { }
  virtual void printValue() const
  { cout << "Integer: " << m_val << endl; }

  private: 
    int m_val;
};

struct TestDouble : public Test
{
  TestDouble(double val): m_val(val) { }
  virtual void printValue() const
  { cout << "Double: " << m_val << endl; }

  private: 
    double m_val;
};

void takeTest(Test& p_test)
{
  p_test.printValue();
}

typedef mpl::map <
    mpl::pair<int, TestInt>
  , mpl::pair<double, TestDouble>
  > test_map;

template <class T>
struct get_type
{
  typedef typename mpl::at<test_map, T>::type type;
};

template <class T> typename get_type<T>::type
getTest (T p_val)
{
  typedef typename mpl::at<test_map, T>::type ret_type;
  ret_type test (p_val);
  return test;
}

int main (void)
{
  cout << "Mpl::Map test" << endl;
  get_type<int>::type t = getTest(5);
  takeTest(t);
}
