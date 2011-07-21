#ifndef Base_h_INCLUDED
#define Base_h_INCLUDED

#include <PerlCppSrc.hxx>
#include <string>
#include <vector>

class DLLPerlCppSrc Base
{
  public:
    Base ();

    void setInt (const int& p_i);
    const int& getInt (void) const;

    void setString (const std::string& p_s);
    const std::string& getString() const;

    void addItem (const std::string& p_s);

    const std::vector<std::string>& getVector () const {
      return m_vs;
    }

    virtual void virtualFun (void) = 0;

    virtual ~Base ();

  private:
    int m_i;
    std::string m_s;
    std::vector<std::string> m_vs;
};

#endif
