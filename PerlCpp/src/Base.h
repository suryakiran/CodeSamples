#ifndef Base_h_INCLUDED
#define Base_h_INCLUDED

#include <vector>
#include <utility>
#include <string>

typedef std::vector<std::string> StringVec;
typedef std::pair<std::string, std::string> StringPair;
typedef std::vector<StringPair> StringPairVec;

#include <PerlCppSrc.hxx>
#include <Accessor.h>

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

    Accessor<std::string> name;
    Accessor<StringVec> stringVecVar;   
    Accessor<bool> boolVar;

  private:
    int m_i;
    std::string m_s;
};

#endif
