#include <iostream>
#include <stdlib.h>

using namespace std;

struct Treap {
  typedef struct _Node {
    long long x, y, cnt, times;//x es el valor, y es la prioridad, cnt el numero elementos en el subarbol
    _Node *l, *r;
 
    _Node(long long _x, long long _y) : x(_x), y(_y), cnt(1), times(1), l(NULL), r(NULL) {}
    ~_Node() { delete l; delete r; }
    /*void recalc() {//Aqui se actualizaria cualquier valor que se lleve en los nodos
      cnt = 1;
			cnt += ((l)?(l->cnt):0);
			cnt += ((r)?(r->cnt):0);
    }*/
  } *Node;
 	
	Node root;
  Treap() : root(NULL) {}
  ~Treap() { delete root; }

  Node merge(Node l, Node r) {
    if (!l || !r) return l ? l : r;
    if (l->y >= r->y) {
      l->r = merge(l->r, r);
      //l->recalc();
      return l;
    } else {
      r->l = merge(l, r->l);
     // r->recalc();
      return r;
    }
  }
 
  void splitByValue(Node v, long long x, Node &l, Node &r) {//Hace split por valor, en l quedan los < x, en r los >= x
    l = r = NULL;
    if (!v) return;
    if (v->x < x) {
      splitByValue(v->r, x, v->r, r);
      l = v;
    } else {
      splitByValue(v->l, x, l, v->l);
      r = v;
    }
   // v->recalc();
  }

	
	//OJO: no se esta comprobando que no haya duplicados. Si lo quisieramos asegurar
	//podriamos mantener el minimo de un subarbol, y tras hacer el split checamos,
	//o si queremos que pueda haber duplicados, tener un campo como times.
  void insertOrderedByValue(long long x, long long y) {
    Node l, r;
    splitByValue(root, x, l, r);
    if(l != NULL)  {
        if(l->x == x && l->y == y)    {
            (l->times)++;
            return;
        }
    }
    if(r != NULL)   {
        if(r->x == x && r->y == y)  {
            (r->times)++;
            return;
        }
    }
    root = merge(merge(l, new _Node(x,y)), r);
  }

  void eraseByValue(long long x, long long y) {
    Node l, m, r;
    splitByValue(root, x, l, m);
    if(l != NULL) {
        if(l->x == x && l->y == y)    {
            (l->times)--;
            if(l->times > 0)
                return;
        }
    }
    if(m != NULL)   {
        if(m->x == x && m->y == y)  {
            (m->times)--;
            if(m->times > 0)
                return;
        }
    }
    splitByValue(m, x+1 , m, r);
    delete m;
    root = merge(l, r);
  }
  
  bool intersect(Node v, long long x, long long y)    {
        if(v == NULL) 
            return false;
        if(x > v->y)
            return false;
        //while(v->y > x) {
        if(v->x < y && v->y > x)
            return true;
    
        return intersect(v->l, x, y) || intersect(v->r, x, y);
    }
    
  long long size() const { return root ? root->cnt : 0; }
};
   
   

int main()  {
    long long N,a,b,aux;
    Treap t;
    char op;
    cin >> N;
    while(N--)  {
        cin >> op >> a >> b;
        op == 'P' ? aux=1 : (op == 'E' ? aux=2 : (op == 'I' ? aux=3 : aux=-1));
        switch(aux) {
            case(1):    {
                t.intersect(t.root,a,b) ? cout << 1 : cout << 0;
                cout << endl;
                break;
            }
            case(2):    {
                t.eraseByValue(a,b);
                break;
            }
            case(3):    {
                t.insertOrderedByValue(a,b);
                break;
            }
        }
    }
}
