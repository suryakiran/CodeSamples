#ifndef heap_hpp
#define heap_hpp 1

#include <std.hxx>
#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/add_reference.hpp>

fmt fileNameFmt (fmt ("heap-%1%.gv"));

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
    int m_fileNum;

  public:
    heap ()
      : m_fileNum (0)
    {
    }

    heap (container_cref p_container) 
      : m_container (p_container), m_fileNum(0)
    {
      build_heap();
    }

    void add (const_reference p_item)
    {
      m_container.push_back (p_item);
      percolate_up();
    }

    void removeMin ()
    {
      value_type tmp = *(m_container.rbegin());
      m_container[0] = tmp;
      m_container.pop_back();
      if (!m_container.empty()) {
        percolate_down (0, m_container.size());
      }
    }

    const_reference getMin() const
    {
      return m_container[0];
    }

    void print (const string& p_label)
    {
      fstream fout;
      fout.open ((fileNameFmt % ++m_fileNum).str().c_str(), ios_base::out);
      fout << "graph \"\" {" << endl;
      fout << "rankdir=TB" << endl;
      fout << fmt("label=\"%1%\"") % p_label << endl;
      int count (0);
      BOOST_FOREACH (int i, m_container)
      {
        fout << fmt("node%1% [label=%2%]") % count++ % i << endl;
      }

      for (size_t i = 0; i < m_container.size(); ++i)
      {
        if ((2*i + 1) < m_container.size()) {
          fout << fmt("node%1% -- node%2%") % i % (2*i + 1) << endl;
        }

        if ((2*i + 2) < m_container.size()) {
          fout << fmt("node%1% -- node%2%") % i % (2*i + 2) << endl;
        }
      }

      fout << "}" << endl;
      fout.close();
    }

    size_t size()
    {
      return m_container.size();
    }

    bool empty ()
    {
      return m_container.empty();
    }

    void sort()
    {
      container& c = m_container;
      size_t sz (c.size());

      while (sz) 
      {
        --sz;
        swap (c[0], c[sz]);
        percolate_down (0, sz);
      }
    }

  private:
    void build_heap()
    {
      size_t s (m_container.size());
      for (size_t i = s/2; i > 0; i--)
      {
        size_t ci (i-1);
        percolate_down (ci, m_container.size());
      }
    }

    void percolate_down(size_t p_idx, size_t p_size)
    {
      size_t idx, child;
      container& c = m_container;

      value_type tmp (c[p_idx]);

      for (idx = p_idx; idx < p_size/2; idx = child)
      {
        child = 2*idx + 1;
        if (child != (p_size-1) && c[child + 1] < c[child]) {
          child ++;
        }
        if (c[child] < tmp) {
          c[idx] = c[child];
        }
        else break;
      }

      c[idx] = tmp;
    }

    void percolate_up ()
    {
      container& c = m_container;
      size_t child (c.size() - 1);
      size_t parent ((child - 1) / 2);
      value_type tmp (c[child]);

      for (child = (c.size()-1); tmp < c[parent]; child = parent, parent = (child - 1)/2)
      {
        c[child] = c[parent];
        if (parent == 0) {
          break;
        }
      }
      c[child] = tmp;
      percolate_down (parent, c.size());
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
