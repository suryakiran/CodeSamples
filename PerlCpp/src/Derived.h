#ifndef Derived_h_INCLUDED
#define Derived_h_INCLUDED

#include "Base.h"

class Derived : public Base
{
  public:
    Derived ();

    void setDouble (const double& p_d);
    const double& getDouble (void) const;

    virtual void virtualFun (void);

    ~Derived ();

  private:
    double m_d;
};

#endif
