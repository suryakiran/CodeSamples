#include "std.hxx"

int main (void)
{
  stl::IntList pre_order, in_order;

  pre_order += 100, 50, 25, 15, 30, 60, 150, 140, 130, 145, 175, 165, 200;
  in_order += 15, 25, 30, 50, 60, 100, 130, 140, 145, 150, 165, 175, 200;
  stl::IntSet visited;
  stl::IntList left, right;

  BOOST_FOREACH (int p, pre_order)
  {
    stl::IntListIter in_iter = find (in_order.begin(), in_order.end(), p);
    copy (in_order.begin(), in_iter, back_inserter(left));
    ++in_iter;
    copy (in_iter, in_order.end(), back_inserter(right));
    printContainer("Left List", left);
    printContainer("Right List", right);
    left.clear();
    right.clear();
  }
}
