#ifndef heap_hpp
#define heap_hpp 1

#include <vector>
#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/lambda/bind.hpp>
using namespace boost::lambda;

template <class T>
class heap
{
  private:
    typedef std::vector<T> container;
    typedef typename container::value_type value_type;
    typedef typename container::reference reference;
    typedef typename container::const_reference const_reference;
    typedef typename container::const_pointer const_pointer;
    typedef typename container::pointer pointer;

    typedef typename boost::add_const<container>::type const_container;
    typedef typename boost::add_reference<container>::type container_ref;
    typedef typename boost::add_reference<const_container>::type container_cref;

  private:
    container m_container;

  public:
    heap ()
    {
    }

    heap (container_cref p_container) 
      : m_container (p_container)
    {
      build_heap();
    }

    void add (const_reference p_item)
    {
      m_container.push_back (p_item);
      modify_heap();
    }

    void removeMin ()
    {
    }

    void print ()
    {
      for_each (m_container.begin(), m_container.end(), cout << _1 << ", ") ;
      cout << endl;
    }

  private:
    void build_heap()
    {
      int h (height());
      int level (h-1);
    }

    void modify_heap ()
    {
    }

    int height()
    {
      if (m_container.empty())
        return 0;

      int s (m_container.size());
      int cumulative(0), h(1);

      while (1)
      {
        cumulative |= (1 << h);
        cout << cumulative << endl;
        h++;
        if (cumulative >= (s-1))
          break;
      }

      cout << "Height: " << h << endl;
      return h;
    }
};

#endif
