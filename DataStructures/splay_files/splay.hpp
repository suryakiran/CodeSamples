#ifndef splay_hpp
#define splay_hpp 1

#include <std.hxx>

struct splay_node;

class splay
{
  private:
    splay_node* m_root;
    splay_node* m_null;
    bool find (int val, splay_node*& root);
    void printTree (splay_node* root);
    void remove (int, splay_node*);
    void rotateRight(splay_node*);
    void rotateLeft(splay_node*);
    bool splayNode (splay_node*);

    int m_fileNum;

  public:
    splay();
    ~splay();

    splay& operator += (int val)
    {
      return insert(val);
    }

    splay& operator, (int val)
    {
      return insert(val);
    }

    pair<int, int> range (int);

    splay& insert (int val);
    bool find (int val);
    void print(const string& p_label);
    int findMin ();
    int findMax() ;
    void remove (int val);
};

#endif
