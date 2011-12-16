#include <std.hxx>

struct TestBase 
{
  virtual void fun () {
    cout << "TestBase::fun" << endl;
  }
};

struct TestDerived : public TestBase
{
  virtual void fun() {
    cout << "TestDerived::fun" << endl;
  }
};

struct Base
{
  public:
    Base () {
    }

    virtual ~Base() {
    }

    virtual TestBase* tclone() {
      return (new TestBase());
    }
    
    virtual Base* clone (){
      return (new Base());
    }

  private:
    Base(const Base&);
    Base& operator= (const Base&);
};

struct Derived : public Base
{
  public:
    Derived() {
    }

    ~Derived() {
    }

    virtual Derived* clone () {
      return (new Derived());
    }

    virtual TestDerived* tclone () {
      return (new TestDerived());
    }
};

int main (void)
{
  unique_ptr<Base> d (new Base);
  Base* t = d->clone();

  TestBase* tb = d->tclone();
  tb->fun() ;
}
