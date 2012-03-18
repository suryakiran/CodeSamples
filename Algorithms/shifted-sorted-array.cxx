#include <std.hxx>

void getIndex (const stl::IntVector& vi, size_t beg, size_t end)
{
  size_t middle = (beg+end) / 2;

  if (vi[beg] > vi[middle]) {
    getIndex (vi, beg, middle);
  } else if (vi[middle+1] > vi[end]){
    getIndex (vi, middle+1, end);
  } else 
    cout << "Index: " << middle+1 << endl;

}

int main (void)
{
  stl::IntVector vi;
  vi += 8, 9, 10, 11, 12, 13, 14, 15, 16, 0, 1, 2, 3, 4, 5, 6, 7;
  printContainer ("HE HE", vi);
  getIndex (vi, 0, vi.size()-1);
}
