#ifndef Derived_h_INCLUDED
#define Derived_h_INCLUDED

#include <PerlCppSrc.hxx>
#include "Base.h"

class DLLPerlCppSrc Derived : public Base
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
