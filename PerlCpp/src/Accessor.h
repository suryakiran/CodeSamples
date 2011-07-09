#ifndef Accessor_h_INCLUDED
#define Accessor_h_INCLUDED

template <class T>
class Accessor
{
  private:
    T m_t;

  public:
    Accessor ()
    {
    }

    /*
     * Explicit constructor, to avoid assignment.
     */

    explicit Accessor (const T& t)
      : m_t(t) 
    {
    }

    T& operator() () 
    {
      return m_t;
    }

    const T& operator() () const 
    {
      return m_t;
    }

    void operator() (const T& t)
    {
      m_t = t;
    }
};

#endif
