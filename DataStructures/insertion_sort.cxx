#include <std.hxx>

int main (void)
{
  vector<int> vi;
  vi += 10, 2, 3, 15, 30, 1, 5, 40, 12, 11, 50, 34, 20, 18, 80;

  printContainer("Initial Array:", vi);

  for (int i = 1; i < vi.size(); ++i)
  {
    int tmp = vi[i];
    int j = i - 1;
    while (tmp < vi[j] && j >= 0)
    {
      vi[j+1] = vi[j--];
    }
    vi[j+1] = tmp;
  }

  printContainer ("Sorted Array:", vi);
}
