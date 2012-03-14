#include "std.hxx"
#include <binary_tree.hpp>
using namespace std;

template <class Iterator>
void
build_tree (boost::iterator_range <Iterator> post_range, bst& tree)
{
  if (!post_range) {
    return;
  }

  typedef typename boost::iterator_range<Iterator>::value_type value_type;

  value_type root = post_range.back();
  tree += root;
  post_range.advance_end (-1);

  if (post_range) {
    auto iter = boost::range::find_if (post_range, bind2nd (greater<value_type>(), root));
    build_tree (boost::make_iterator_range(post_range.begin(), iter), tree);
    build_tree (boost::make_iterator_range(iter, post_range.end()), tree);
  }
}

template <class InputIterator, class OutputIterator>
void
build_preorder (boost::iterator_range<InputIterator> range, OutputIterator destination)
{
  if (!range) {
    return;
  }

  typedef typename boost::iterator_range<InputIterator>::value_type value_type;
  value_type root = range.back();
  *destination = root;
  ++destination;
  range.advance_end(-1);

  if (range) {
    auto iter = boost::range::find_if (range, bind2nd (greater<value_type>(), root));
    build_preorder (boost::make_iterator_range (range.begin(), iter), destination);
    build_preorder (boost::make_iterator_range (iter, range.end()), destination);
  }
}

int main (void)
{
  cout << boolalpha;
  bst b;

  stl::IntVector post_order, in_order;
  stl::IntVector pre_order (post_order.size());

  post_order += 10, 30, 40, 50, 80, 250, 225, 200, 180, 160, 150, 100;
  in_order += 15, 25, 30, 50, 60, 100, 130, 140, 145, 150, 165, 175, 200;

  build_tree (boost::make_iterator_range (post_order), b);
  build_preorder (boost::make_iterator_range (post_order), back_inserter(pre_order));
  printContainer ("Pre Order", pre_order);
  b.print();
}
