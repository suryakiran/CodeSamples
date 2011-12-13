#include <dlist.hpp>

struct dlist_node
{
  dlist_node(int p_val)
    : m_val (p_val), m_next(0), m_prev(0) { }

  int m_val;
  Node m_next;
  Node m_prev;
};

void
dlist::push (int i)
{
  Node n = new dlist_node (i);

  if (!m_head) {
    m_head = n;
  }

  else {
    Node p;
    for (p = m_head; p && p->m_next; p = p->m_next);
    p->m_next = n;
    n->m_prev = p;
  }
}

void 
dlist::print ()
{
  m_fileNum++;
  string fileName ((boost::format ("dlist-%1%.gv") % m_fileNum).str());

  fstream fout ;
  fout.open (fileName.c_str(), ios_base::out);
  fout << "digraph \"\" {" << endl;
  fout << "rankdir=LR;" << endl;
  fout << "node [shape=box];" << endl;

  int i(0);
  for (Node p = m_head; p; p = p->m_next)
  {
    fout << boost::format("node%1% [label=\"%2%\"];") % i % p->m_val << endl;
    if (p->m_next) {
      fout << boost::format("node%1%->node%2%;") % i % (i+1) << endl;
    }
    i++;
  }

  fout << "}" << endl;
  fout.close();
}

void dlist::reverse()
{
  Node p,q,r;

  p = m_head;
  q = m_head->m_next;
  p->m_next = (Node)0;

  while (q)
  {
    r = q->m_next;
    q->m_next = m_head;
    q->m_prev = r;
    m_head->m_prev = q;
    m_head = q;
    q = r;
  }
}
