#ifndef Example_h_INCLUDED
#define Example_h_INCLUDED

#include <string>

class Example
{
  public:
    Example ();

    void setInt (const int& p_i);
    const int& getInt (void) const;

    void setString (const std::string& p_s);
    const std::string& getString() const;

    ~Example ();

  private:
    int m_i;
    std::string m_s;
};

#endif
