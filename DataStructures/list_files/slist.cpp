#include <slist.hpp>

struct slist_node
{
  slist_node(int p_val)
    : m_val (p_val), m_next(0) { }

  ~slist_node() {
    cout << "Deleting: " << m_val << endl;
    delete m_next;
  }

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
  string fileName ((boost::format ("slist-%1%.gv") % m_fileNum).str());
  for (Node p = m_head; p; p = p->m_next)
  {
    cout << p->m_val << ',';
  }
  cout << endl;
}

void slist::reverse()
{
  Node p,q,r;

  Node cur, next, prev;
  cur = m_head;
  prev = (Node) 0;

  while (cur)
  {
    next = cur->m_next;
    cur->m_next = prev;
    prev = cur;
    cur = next;
  }

  m_head = prev;

#if 0
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
#endif
}

slist::~slist()
{
  if (m_head) {
    delete m_head;
  }
}
