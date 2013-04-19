#include <std.hxx>
#include <tbb/task_scheduler_init.h>
#include <tbb/blocked_range.h>
#include <tbb/parallel_for.h>

struct Test
{
  Test(int i, const stl::IntVector& vi) : m_i(i), m_vi(vi) {}
public:
  void operator() (const tbb::blocked_range<size_t>& r) const {
    for (size_t i = r.begin();
         i != r.end(); ++i) {
      cout << m_vi[i] << endl;
    }
    
  }

  int m_i;
  stl::IntVector m_vi;
};

int main (void)
{
  tbb::task_scheduler_init init;
  stl::IntVector vi;
  vi += 1,2,3,4,5,6,7,8,9,10;
  tbb::parallel_for(tbb::blocked_range<size_t>(0, vi.size(), 1), Test(10, vi));
}
