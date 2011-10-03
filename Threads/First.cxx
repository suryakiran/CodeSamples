#include <boost/thread.hpp>
#include <iostream>
#include <iomanip>
using namespace std;

struct Callable
{
  void operator() () const
  {
    cout << "Callable Function" << endl;
    cout << '%' << boost::this_thread::get_id() << '%' << endl;
  }
};

int main (void)
{
  cout << "Threads Sample" << endl;
  Callable c;
  boost::thread t (c);
  cout << '-' << boost::this_thread::get_id() << '-' << endl;
  t.join();
}
