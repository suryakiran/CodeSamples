#include <std.hxx>

typedef vector<int> IntV;
typedef IntV::iterator Iter;
typedef IntV::const_iterator IterC;
typedef IntV::reverse_iterator IterR;
typedef IntV::const_reverse_iterator IterRC;
typedef boost::tuple <Iter, Iter> IterTwo;

void insertion_sort (IntV p_vi)
{
  printContainer("Initial Array:", p_vi);
  for (int i = 1; i < p_vi.size(); ++i)
  {
    int tmp = p_vi[i];
    int j = i - 1;
    while (tmp < p_vi[j] && j >= 0)
    {
      p_vi[j+1] = p_vi[j--];
    }
    p_vi[j+1] = tmp;
    printContainer ((boost::format ("pass: %1%") % i), p_vi, ':', false);
  }
  printContainer ("Sorted Array: (Insertion Sort)", p_vi);
}
 
void merge (IntV& p_vi, size_t beg, size_t middle, size_t end)
{
  IntV tmp ;
  size_t left = beg, right = middle+1;
  size_t numElem = end - beg + 1;

  while (left <= middle && right <= end)
  {
    if (p_vi[left] <= p_vi[right]) {
      tmp.push_back (p_vi[left++]);
    }
    else {
      tmp.push_back (p_vi[right++]);
    }
  }

  while (left <= middle) {
    tmp.push_back (p_vi[left++]);
  }
  while (right <= end) {
    tmp.push_back (p_vi[right++]);
  }

  for (IterR i = tmp.rbegin(); i != tmp.rend(); ++i)
  {
    p_vi [end--] = *i;
  }
}


void merge (IntV& p_vi, size_t beg, size_t end)
{
  if (beg < end)
  {
    size_t middle = (beg + end) / 2;
    merge (p_vi, beg, middle);
    merge (p_vi, middle + 1, end);
    merge (p_vi, beg, middle, end);
  }
}

void merge_sort (IntV p_vi)
{
  printContainer ("Original", p_vi);
  merge (p_vi, 0, p_vi.size()-1);
  printContainer ("Sorted (merge sort)", p_vi);
}

void quick_sort (IntV p_vi)
{
  printContainer ("Original", p_vi);
  quickSort (p_vi, 0, p_vi.size()-1);
  printContainer ("Sorted (merge sort)", p_vi);
}

int main (void)
{
  IntV vi;
  vi += 10, 2, 3, 15, 30, 1, 5, 40, 12, 11, 50, 34, 20, 18, 80;
  //insertion_sort (vi);
  quick_sort (vi);
  merge_sort (vi);
}
