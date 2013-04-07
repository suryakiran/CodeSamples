#include <std.hxx>
#include <tbb/task_scheduler_init.h>

int main (void)
{
  tbb::task_scheduler_init init;
  cout << "First TBB Example" << endl;
}
