#include <std.hxx>

struct Top
{
  Top(int a)
  {
    cout << BOOST_CURRENT_FUNCTION << endl;
  }

  virtual void fun()
  {
    cout << BOOST_CURRENT_FUNCTION << endl;
  }

  private:
    Top()
    {
      cout << BOOST_CURRENT_FUNCTION << endl;
    }

};

struct MiddleLeft : public virtual Top
{
#if 0
  MiddleLeft()
  {
    cout << BOOST_CURRENT_FUNCTION << endl;
  }
#endif

  MiddleLeft(int a)
    :Top(a)
  {
    cout << BOOST_CURRENT_FUNCTION << endl;
  }

  virtual void fun()
  {
    cout << BOOST_CURRENT_FUNCTION << endl;
  }
};

struct MiddleRight : public virtual Top
{
#if 0
  MiddleRight()
  {
    cout << BOOST_CURRENT_FUNCTION << endl;
  }
#endif

  MiddleRight(int a)
    :Top(a)
  {
    cout << BOOST_CURRENT_FUNCTION << endl;
  }

  virtual void fun()
  {
    cout << BOOST_CURRENT_FUNCTION << endl;
  }
};

struct Bottom : public MiddleLeft, public MiddleRight
{
#if 0
  Bottom()
  {
    cout << BOOST_CURRENT_FUNCTION << endl;
  }
#endif

  Bottom(int a)
    :Top(a), MiddleLeft(a), MiddleRight(a)
  {
    cout << BOOST_CURRENT_FUNCTION << endl;
  }

  virtual void fun()
  {
    cout << BOOST_CURRENT_FUNCTION << endl;
    MiddleRight::fun();
    MiddleLeft::fun();
  }
};

int main (void)
{
  Bottom b(2);
}
