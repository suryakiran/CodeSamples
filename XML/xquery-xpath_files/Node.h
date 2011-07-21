#ifndef Node_h_INCLUDED
#define Node_h_INCLUDED

#include <xqilla/xqilla-simple.hpp>
#include <SafeBool.h>
#include <map>
#include <vector>
using namespace std;

typedef vector<string> StringVec;
typedef map<string, string> StringMap;
typedef map<string, StringVec> TextChildren;

namespace Xqilla {

typedef const char* CString;

class String
{
  public:
    String (const XMLCh* p_xmlch)
      :m_xmlch(p_xmlch) { }

    operator string() const
    {
      return std::string(UTF8(m_xmlch));
    }

    operator CString() const
    {
      return UTF8(m_xmlch);
    }

  private:
    const XMLCh* m_xmlch;
};

class Node : public SafeBool<Node>
{ 
  friend class SafeBool<Node>;
  typedef ::Node::Ptr NodePtr;
  public:
    Node (const Item::Ptr p_item, const DynamicContext* p_context, const LocationInfo* p_location)
      :m_context(p_context), m_location(p_location)
    {
      if (p_item->isNode()) {
        m_nodePtr = p_item;
      }
    }

    NodePtr parent () const;

    StringMap attributes();
    TextChildren textChildren();

    string name () const {
      return String(m_nodePtr->dmNodeName(m_context)->getName());
    }

    string value() const;

    const NodePtr& operator->() const {
      return m_nodePtr;
    }

  private:
      bool bool_test() const {
        return m_nodePtr.isNull() ? false : true;
      }

  private:
    const ::DynamicContext* m_context;
    const ::LocationInfo*   m_location;
    NodePtr m_nodePtr;
};

}

#endif
