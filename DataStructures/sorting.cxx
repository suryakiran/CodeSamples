#include <std.hxx>

void insertion_sort (stl::IntVector v)
{
  printContainer ("Original", v);

  size_t sz (v.size());
  for (size_t i = 1; i < sz; ++i)
  {
    int tmp = v[i];
    size_t j (i-1);
    for (; j >= 0 && v[j] > tmp; j--)
    {
      v[j+1] = v[j];
      if (j == 0) {
        break;
      }
    }
    if (!j) {
      v[0] = tmp;
    } else {
      v[j+1] = tmp;
    }

    printContainer (fmt("Pass: %1%") % i, v);
  }
}

void merge (stl::IntVector& v, size_t beg, size_t middle, size_t end)
{
  size_t i, j;
  stl::IntVector tmp;
  for (i = beg, j = middle+1; i <= middle && j <= end; )
  {
    if (v[i] < v[j]) {
      tmp.push_back(v[i++]);
    } else {
      tmp.push_back(v[j++]);
    }
  }

  while (i <= middle) {
    tmp.push_back (v[i++]);
  }

  while (j <= end) {
    tmp.push_back (v[j++]);
  }

  for (i = 0, j = beg; i < tmp.size();)
  {
    v[j++] = tmp[i++];
  }

  printContainer((fmt("(%1%, %2%)") % beg % end), v); 
}

void merge_sort (stl::IntVector& v, size_t beg, size_t end)
{
  if (beg < end) {
    size_t middle = (beg + end)/2;
    merge_sort (v, beg, middle);
    merge_sort (v, middle+1, end);
    merge (v, beg, middle, end);
  }
}

int main (void)
{
  stl::IntVector vi;
  vi += 10,5,18,3,17,2,9,1,0,11;

//  insertion_sort (vi);
  merge_sort (vi, 0, vi.size()-1);
}
