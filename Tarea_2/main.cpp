#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <math.h>

using namespace std;

void pirates_ahoy();
void cambia_bucaneros(vector<int> &tree, vector<queue<int>> &lazy, int a, int b, int n);
void cambia_barbaros(vector<int> &tree, vector<queue<int>> &lazy, int a, int b, int n);
void cambia_inverso(vector<int> &tree, vector<queue<int>> &lazy, int a, int b, int n);
void cuantos_bucaneros(vector<int> &tree, vector<queue<int>> &lazy, int a, int b, int con, int n);
void updateRangeUtil(vector<int> &tree, vector<queue<int>> &lazy, int si, int ss, int se, int us, int ue, int dif);
int getSumUtil(vector<int> &tree, vector<queue<int>> &lazy, int ss, int se, int qs, int qe, int si);
void construye_lazy(vector<queue<int>> &t, int pos, int a, int b, int ms);
void construye_seg_tree(vector<int> &t, vector<int> &A, int pos, int a, int b);

int main()
{
    pirates_ahoy();
    return 0;
}

void pirates_ahoy() {
    int n,m,k,t,a,b,con,tam;
    char ch;

    cin >> n;
    for(int i=0; i<n; i++)  {
        cout << "Case " << i+1 << ":" <<endl;
        cin >> m;
        vector<int> vec;
        for(int j=0; j<m; j++)  {
            string p,aux;
            cin >> k; cin >> p;
            for(int kj=0; kj<k; kj++)   {
                for(int ij=0; ij<(int)p.size(); ij++)   {
                    aux = p[ij];
                    vec.push_back(stoi(aux));
                }
            }
        }
        tam = (int)vec.size();
        vector<int> tree;               // Vector del segment tree donde se guardará el número de Bucaneros.
        vector<queue<int>> lazy;        // Vector lazy en el que se almacena en forma de cola las operaciones pendientes.

        /** Pedimos memoria para el segment tree y para el lazy tree**/
        int x = (int)(ceil(log2(tam)));     // Altura que tendrá el segment tree
        int max_size = 2*(int)pow(2, x)-1;              // Máximo número de nodos que tiene el s. tree
        tree.reserve(max_size);

        /** Construimos el segment tree y el lazy tree**/
        construye_seg_tree(tree,vec,1,0,tam-1);
        construye_lazy(lazy,1,0,tam-1,max_size);
        vec.clear();

        /** Respondemos las preguntas **/
        cin >> t;
        con = 1;
        for(int j=0; j<t; j++)  {
            cin >> ch;
            cin >> a >> b;
            switch(ch)  {
                case 'F':
                    cambia_bucaneros(tree,lazy,a,b,tam-1);
                    break;
                case 'E':
                    cambia_barbaros(tree,lazy,a,b,tam-1);
                    break;
                case 'I':
                    cambia_inverso(tree,lazy,a,b,tam-1);
                    break;
                case 'S':
                    cuantos_bucaneros(tree,lazy,a,b,con,tam-1);
                    con++;
                    break;
            }
        }
        tree.clear();
        lazy.clear();
    }
}

void cambia_bucaneros(vector<int> &tree, vector<queue<int>> &lazy, int a, int b, int n)   {
    updateRangeUtil(tree,lazy,1,0,n,a,b,1);
}

void cambia_barbaros(vector<int> &tree, vector<queue<int>> &lazy, int a, int b, int n)    {
    updateRangeUtil(tree,lazy,1,0,n,a,b,2);
}

void cambia_inverso(vector<int> &tree, vector<queue<int>> &lazy, int a, int b, int n) {
    updateRangeUtil(tree,lazy,1,0,n,a,b,3);
}

void cuantos_bucaneros(vector<int> &tree, vector<queue<int>> &lazy, int a, int b, int con, int n) {
    int aux = getSumUtil(tree,lazy,0,n,a,b,1);
    cout << "Q" << con << ": " << aux << endl;
}

int getSumUtil(vector<int> &tree, vector<queue<int>> &lazy, int ss, int se, int qs, int qe, int si)  {
    while(!lazy[si].empty())   {
        int aux = lazy[si].front();
        switch (aux)    {
            case 1:
                tree[si] += se-ss+1;
                if(tree[si] > se-ss+1)
                    tree[si] = se-ss+1;
                break;
            case 2:
                tree[si] -= se-ss+1;
                if(tree[si] < 0)
                    tree[si] = 0;
                break;
            case 3:
                tree[si] = tree[si] - (se-ss+1);
                if(tree[si] < 0)
                    tree[si] *= -1;
                break;
        }
        if(ss != se)    {
            lazy[si*2].push(aux);
            lazy[si*2+1].push(aux);
        }
        lazy[si].pop();
    }
    if(ss>se || ss>qe || se<qs)
        return 0;
    if(ss>=qs && se<=qe)
        return tree[si];
    int mid = (ss+se)/2;

    return getSumUtil(tree,lazy,ss,mid,qs,qe,2*si) + getSumUtil(tree,lazy,mid+1,se,qs,qe,2*si+1);
}

void updateRangeUtil(vector<int> &tree, vector<queue<int>> &lazy, int si, int ss, int se, int us, int ue, int dif)   {
    while(!lazy[si].empty())   {
        int aux = lazy[si].front();
        switch (aux)    {
            case 1:
                tree[si] += se-ss+1;
                if(tree[si] > se-ss+1)
                    tree[si] = se-ss+1;
                break;
            case 2:
                tree[si] -= se-ss+1;
                if(tree[si] < 0)
                    tree[si] = 0;
                break;
            case 3:
                tree[si] = tree[si] - (se-ss+1);
                if(tree[si] < 0)
                    tree[si] *= -1;
                break;
        }
        if(ss != se)    {
            lazy[si*2].push(aux);
            lazy[si*2+1].push(aux);
        }
        lazy[si].pop();
    }
    if(ss>se || ss>ue || se<us)
        return;
    if(ss>=us && se<=ue)    {
        switch (dif)    {
            case 1:
                tree[si] += se-ss+1;
                if(tree[si] > se-ss+1)
                    tree[si] = se-ss+1;
                break;
            case 2:
                tree[si] -= (se-ss+1);
                if(tree[si] < 0)
                    tree[si] = 0;
                break;
            case 3:
                tree[si] = tree[si] - (se-ss+1);
                if(tree[si] < 0)
                    tree[si] *= -1;
                break;
        }
        if(ss != se)    {
            lazy[si*2].push(dif);
            lazy[si*2+1].push(dif);
        }
        /*for(int R=si/2; R>=1; R=R/2)
            tree[R] = tree[R*2] + tree[R*2+1];*/
        return;
    }
    int mid = (ss+se)/2;
    updateRangeUtil(tree,lazy,si*2,ss,mid,us,ue,dif);
    updateRangeUtil(tree,lazy,si*2+1,mid+1,se,us,ue,dif);
    tree[si] = tree[si*2] + tree[si*2+1];
}

void construye_seg_tree(vector<int> &t, vector<int> &A, int pos, int a, int b)	{
	if(a == b)
		t[pos] = A[a];
	else 	{
		int mid = (a+b)/2;
		construye_seg_tree(t, A, 2*pos, a, mid);
		construye_seg_tree(t, A, 2*pos+1,mid+1, b);
		t[pos] = t[2*pos] + t[2*pos+1];
	}
}

void construye_lazy(vector<queue<int>> &t, int pos, int a, int b, int ms)	{
	/*if(a == b)  {
        queue<int> aux;
        t[a] = aux;
	}
	else 	{
		int apos = 2*pos,  bpos = 2*pos+1;
		construye_lazy(t, apos, a, (int)((a+b)/2));
		construye_lazy(t, bpos, (int)((a+b)/2) + 1, b);
		queue<int> aux;
        t[pos] = aux;
	}*/
	for(int i=0; i<ms; i++) {
        queue<int> aux;
        t.push_back(aux);
    }
}
