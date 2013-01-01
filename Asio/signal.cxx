#include "std.hxx"
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/signals2.hpp>

boost::mutex global_stream_lock;

struct Test
{
  boost::asio::io_service service;
  shared_ptr<boost::asio::io_service::work> work;

  Test()
  {
    work.reset(new boost::asio::io_service::work (service));
  }

  void someOp ()
  {
    global_stream_lock.lock();
    cout << fmt ("[%1%] Some Bloody Operation") % boost::this_thread::get_id() << endl;
    global_stream_lock.unlock();
    work.reset();
  }

  void post ()
  {
    global_stream_lock.lock();
    cout << fmt ("[%1%] Post") % boost::this_thread::get_id() << endl;
    global_stream_lock.unlock();
    service.post (phx::bind (&Test::someOp, this));
  }

  void loop()
  {
    global_stream_lock.lock();
    cout << fmt ("[%1%] Thread Begin") % boost::this_thread::get_id() << endl;
    global_stream_lock.unlock();
    service.run();
    global_stream_lock.lock();
    cout << fmt ("[%1%] Thread Finish") % boost::this_thread::get_id() << endl;
    global_stream_lock.unlock();
  }
};

int main (void)
{
  global_stream_lock.lock();
  cout << fmt ("[%1%] Signal Example") % boost::this_thread::get_id() << endl;
  global_stream_lock.unlock();
  boost::signals2::signal <void()> sig;
  {
    Test test;
    sig.connect (phx::bind (&Test::post, boost::ref(test)));
    boost::thread t (phx::bind (&Test::loop, boost::ref(test)));
    sig();
    t.join();
  }
}
