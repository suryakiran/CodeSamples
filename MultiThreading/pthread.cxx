#include "std.hxx"
#include <pthread.h>
#include <ctime>
#include <cerrno>
#include <cstring>

int zero;
pthread_t thread_main;
pthread_t thread_a;
pthread_t thread_b;
pthread_t thread_c;
pthread_t thread_d;
pthread_t thread_e;
pthread_attr_t attr;

void
display_error (const string& p_s)
{
  cout << fmt ("Error: %1%") % p_s << endl;
}

void* create_thread_b (void* p_arg)
{
  pthread_t tid = pthread_self();
  cout << fmt("Thread B: %1%") % tid << endl;
  for (int i = 0; i < 5; ++i) {
    cout << fmt ("Thread B: %1%") % i << endl;
    sleep (1);
  }
  //pthread_join (thread_a, NULL);
  cout << "Returning from thread_b" << endl;
  return ((void*)77);
}

void* create_thread_a(void* p_arg)
{
  pthread_t tid = pthread_self();
  cout << fmt("Thread A: %1%") % tid << endl;
  pthread_create (&thread_b, &attr, create_thread_b, NULL);
  for (int i = 0; i < 10; ++i) {
    cout << fmt ("Thread A: %1%") % i << endl;
    sleep (1);
  }
  cout << "Returning from thread_a" << endl;
  return ((void*) 77);
}

int main (void)
{
  int s(0) ;
  zero = time(NULL);
  thread_main = pthread_self();
  s = pthread_attr_init (&attr);
  if (s) {
    display_error ("pthread_attr_init");
  }
  pthread_attr_setscope (&attr, PTHREAD_SCOPE_SYSTEM);
  pthread_attr_setdetachstate (&attr, PTHREAD_CREATE_JOINABLE);

  pthread_create (&thread_a, &attr, create_thread_a, NULL);
  sleep(2);
  s = pthread_join (thread_b, NULL);
  if (s) {
    switch (s) 
    {
      case EDEADLK:
        cout << "EDEADLK Error code" << endl;
        break;
      case EINVAL:
        cout << "EINVAL Error code" << endl;
        break;
      case ESRCH:
        cout << "ESRCH Error code" << endl;
        break;
      default:
        cout << "NO Valid error number" << endl;
        break;
    }
    display_error (strerror (errno));
  }
  cout << "In Main Thread" << endl;
  pthread_exit ((void*) NULL);
}
