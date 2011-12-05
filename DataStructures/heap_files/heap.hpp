#ifndef heap_hpp
#define heap_hpp 1

#include <std.hxx>
#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/add_reference.hpp>

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
      value_type tmp = *(m_container.rbegin());
      m_container[0] = tmp;
      m_container.pop_back();
      if (!m_container.empty()) {
        percolate_down (0);
      }
    }

    const_reference getMin() const
    {
      return m_container[0];
    }

    void print ()
    {
      printContainer ("Current Heap:", m_container);
    }

    size_t size()
    {
      return m_container.size();
    }

    bool empty ()
    {
      return m_container.empty();
    }

  private:
    void build_heap()
    {
      size_t s (m_container.size());
      for (size_t i = s/2; i > 0; i--)
      {
        size_t ci (i-1);
        percolate_down (ci);
      }
    }

    void percolate_down(size_t p_idx)
    {
      size_t idx, child;
      container& c = m_container;

      value_type tmp (c[p_idx]);

      for (idx = p_idx; idx < c.size()/2; idx = child)
      {
        child = 2*idx + 1;
        if (child != (c.size()-1) && c[child + 1] < c[child]) {
          child ++;
        }
        if (c[child] < tmp) {
          c[idx] = c[child];
        }
        else break;
      }

      c[idx] = tmp;
    }

    void modify_heap ()
    {
      container& c = m_container;
      size_t child (c.size() - 1);
      size_t parent ((child - 1) / 2);
      value_type tmp (c[child]);

      for (child = (c.size()-1); parent > 0 && tmp < c[parent]; parent = (child - 1)/2)
      {
        c[child] = c[parent];
      }
      c[parent] = tmp;
      percolate_down (parent);
    }

    int height()
    {
      int s (m_container.size()), h(0);
      while (s) { s = s >> h++; }

      cout << "Height: " << h << endl;
      return h;
    }
};

#endif
