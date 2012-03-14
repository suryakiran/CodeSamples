#include "std.hxx"

#include <boost/thread.hpp>

boost::thread::id id_main, id_a;
boost::thread thread_a, thread_b;

struct do_nothing_a ;
struct do_nothing_b ;

struct do_nothing_b
{
  void operator()()
  {
    for(int i = 0; i < 5; ++i) {
      cout << fmt ("Do Nothing B: %1%") % i << endl;
	  boost::system_time timeout (boost::get_system_time() + boost::posix_time::milliseconds (1000));
	  boost::thread::sleep (timeout);
    }
  }
};

struct do_nothing_a
{
  void operator() ()
  {
    do_nothing_b b;
    thread_b = boost::thread(b);
    for (int i = 0; i < 10; ++i) {
      cout << fmt("Do Nothing A: %1%") % i << endl;
      if (i == 2) {
        thread_b.interrupt();
      }
	  boost::system_time timeout (boost::get_system_time() + boost::posix_time::milliseconds (1000));
	  boost::thread::sleep (timeout);
    }
  }
};

int main (void)
{
  id_main = boost::this_thread::get_id();
  do_nothing_a a;
  thread_a = boost::thread (a);
  boost::system_time timeout (boost::get_system_time() + boost::posix_time::milliseconds (2000));
  boost::thread::sleep (timeout);
  thread_a.join();
}
