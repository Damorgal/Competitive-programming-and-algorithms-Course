#include <stdlib.h>
#include <iostream>
#include <utility>

using namespace std;

struct Treap {
    typedef struct _Node {
        pair<long long, long long> x;
        long long y, min, max, times;//x es el valor del intervalo, y es la prioridad, min es el valor minimo del subarbol y max el maximo en el subarbol
        _Node *l, *r;

        _Node(pair<long long, long long> _x) : x(_x), y((rand() << 16) ^ rand()), min(_x.first), max(_x.second), times(1), l(NULL), r(NULL) {}
        ~_Node() { delete l; delete r; }
        void recalc() {//Aqui se actualizaria cualquier valor que se lleve en los nodos
            min = x.first;
            max = x.second;
            (l) ? (l->min < min ? min=l->min : 0) : 0;
            (r) ? (r->min < min ? min=r->min : 0) : 0;
            (l) ? (l->max > max ? max=l->max : 0) : 0;
            (r) ? (r->max > max ? max=r->max : 0) : 0;
        }
    } *Node;

    Node root;
    Treap() : root(NULL) {}
    ~Treap() { delete root; }

    Node merge(Node l, Node r) {
        if (!l || !r) return l ? l : r;
        // Min heap
        if (l->y < r->y) {
            l->r = merge(l->r, r);
            l->recalc();
            return l;
        } else {
            r->l = merge(l, r->l);
            r->recalc();
            return r;
        }
    }

    // En este caso se ordena por primera entrada, en caso de empate, por segunda entrada
    void splitByValue(Node v, pair<long long, long long> x, Node &l, Node &r) {//Hace split por valor, en l quedan los < x, en r los >= x
        l = r = NULL;
        if (!v) return;
        if (v->x.first < x.first) {
            splitByValue(v->r, x, v->r, r);
            l = v;
        } else if(v->x.first == x.first && v->x.second < x.second)  {
            splitByValue(v->r, x, v->r, r);
            l = v;
        }
        else {
            splitByValue(v->l, x, l, v->l);
            r = v;
        }
        v->recalc();
    }

    void insertOrderedByValue(pair<long long, long long> x) {
        Node l, r, m;
        splitByValue(root, x, l, m);
        splitByValue(m, make_pair(x.first, x.second+1), m, r);
        if(m != NULL)   {
            if(m->x.first == x.first && m->x.second == x.second)    {
                (m->times)++;
                root = merge(l,merge(m,r));
                return;
            }
        }
        root = merge(l, merge(new _Node(x),merge(m,r)));
    }

    void eraseByValue(pair<long long, long long> x) {
        Node l, m, r;
        splitByValue(root, x, l, m);
        splitByValue(m, make_pair(x.first, x.second+1), m, r);
        if(m != NULL)   {
            if(m->x.first == x.first && m->x.second == x.second)    {
                (m->times)--;
                if(m->times > 0)    {
                    root = merge(l,merge(m,r));
                    return;
                }
            }
        }
        delete m;
        root = merge(l, r);
    }

    bool intersect(Node v, pair<long long, long long> x)    {
        if(v == NULL)
            return false;
        if(v->max < x.first || v->min > x.second)
            return false;
        if(v->x.first < x.second && v->x.second > x.first)
            return true;
        if(intersect(v->l, x))
            return true;
        if(intersect(v->r, x))
            return true;
        return false;
    }
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
                t.intersect(t.root,make_pair(a,b)) ? cout << 1 : cout << 0;
                cout << endl;
                break;
            }
            case(2):    {
                t.eraseByValue(make_pair(a,b));
                break;
            }
            case(3):    {
                t.insertOrderedByValue(make_pair(a,b));
                break;
            }
        }
    }
}
