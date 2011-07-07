#ifndef SafeBool_h_INCLUDED
#define SafeBool_h_INCLUDED

template <class Derived>
struct SafeBool
{
  typedef void (SafeBool::*bool_type) () const;

  operator bool_type() const {
    return 
      static_cast<const Derived*>(this)->bool_test() ? &SafeBool::bool_function : 0;
  }

  private:
    void bool_function() const { };
};

#endif
