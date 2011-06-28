#ifndef Base_h_INCLUDED
#define Base_h_INCLUDED

#include <PerlCppSrc.hxx>
#include <string>

class DLLPerlCppSrc Base
{
  public:
    Base ();

    void setInt (const int& p_i);
    const int& getInt (void) const;

    void setString (const std::string& p_s);
    const std::string& getString() const;

    virtual void virtualFun (void) = 0;

    virtual ~Base ();

  private:
    int m_i;
    std::string m_s;
};

#endif
