#include <slist.hpp>

struct slist_node
{
  slist_node(int p_val)
    : m_val (p_val), m_next(0) { }

  int m_val;
  Node m_next;
};

void
slist::push (int i)
{
  Node n = new slist_node (i);

  if (!m_head) {
    m_head = n;
  }

  else {
    Node p;
    for (p = m_head; p && p->m_next; p = p->m_next);
    p->m_next = n;
  }
}

void 
slist::print ()
{
  m_fileNum++;
  string fileName ((boost::format ("list-%1%.gv") % m_fileNum).str());
  for (Node p = m_head; p; p = p->m_next)
  {
    cout << p->m_val << ',';
  }
  cout << endl;
}

void slist::reverse()
{
  Node p,q,r;

  p = m_head;
  q = m_head->m_next;
  p->m_next = (Node)0;

  while (q)
  {
    r = q->m_next;
    q->m_next = m_head;
    m_head = q;
    q = r;
  }
}
