#include <stdlib.h>
#include <cmath>
#include <iostream>
#include <vector>
#include <queue>
#include <string>

using namespace std;
#define optimizar_io ios_base::sync_with_stdio(0);cin.tie(0);

void cambiaUnos(int *tree, int *lazy, int a, int b, int n);
void cambiaCeros(int *tree, int *lazy, int a, int b, int n);
void cambiaInverso(int *tree, int *lazy, int a, int b, int n);
void cuantosUnos(int *tree, int *lazy, int a, int b, int n);
void updateRangeUtil(int *tree, int *lazy, int si, int ss, int se, int us, int ue, int dif);
int getSumUtil(int *tree, int *lazy, int ss, int se, int qs, int qe, int si);
void construyeST(int *t, vector<int> &A, int pos, int a, int b);

int main()  {
    int N, m, Q, t, l, r, tam;
    char op, *p;
    
    scanf("%d",&N);
    //cin >> N;
    while(N--)  {
        scanf("%d",&m);
        //cin >> m;
        vector<int> vec;
        while(m--)  {
            p = (char*)malloc(10000000*sizeof(char));
            scanf("%d %s",&t,p);
            //cin >> t >> p;
            while(t--)   {
                for(int i=0; p[i] != '\0'; i++)   {
                    op = p[i];
                    vec.push_back(atoi(&op));
                }
            }
            free(p);
        }
        tam = (int)vec.size();
        int *tree, *lazy;   // Vector del segment tree donde se guardará el número de unos.
                            // Vector lazy en el que se almacena en forma de cola las operaciones pendientes.

        /** Pedimos memoria para el segment tree y para el lazy tree**/
        // int x = (int)(ceil(log2(tam))); 
        int logtam = 0, aux=tam;
        while(aux >>= 1) logtam++;
        if(1<<logtam < tam) logtam++;       // Altura que tendrá el segment tree
        int max_size = (1<<(logtam+1));     // Máximo número de nodos que tiene el STree
        tree = (int*)malloc(max_size*sizeof(int));
        lazy = (int*)calloc(max_size,sizeof(int));

        /** Inicializamos el segment tree y el lazy tree**/
        construyeST(tree,vec,1,0,tam-1);
        vec.clear();
        
        /** Respondemos las preguntas **/
        scanf("%d",&Q);
        //cin >> Q;
        while(Q--)  {
            scanf("\n%c %d %d", &op, &l, &r);
            //cin >> op >> l >> r;
            if(op == 'F')   {
                cambiaUnos(tree,lazy,l,r,tam-1);
                //printf("F cumplido\n");
            }
            else if(op == 'E')  {
                cambiaCeros(tree,lazy,l,r,tam-1);
                //printf("E cumplido\n");
            }
            else if(op == 'I')  {
                cambiaInverso(tree,lazy,l,r,tam-1);
                //printf("I cumplido\n");
            }
            else if(op == 'S')  {
                cuantosUnos(tree,lazy,l,r,tam-1);
                //printf("S cumplido\n");
            }
        }
        free(tree);
        free(lazy);
    }
    return 0;
}

void cambiaUnos(int *tree, int *lazy, int a, int b, int n)   {
    updateRangeUtil(tree,lazy,1,0,n,a,b,1);
}

void cambiaCeros(int *tree, int *lazy, int a, int b, int n)    {
    updateRangeUtil(tree,lazy,1,0,n,a,b,2);
}

void cambiaInverso(int *tree, int *lazy, int a, int b, int n) {
    updateRangeUtil(tree,lazy,1,0,n,a,b,3);
}

void cuantosUnos(int *tree, int *lazy, int a, int b, int n) {
    int ans = getSumUtil(tree,lazy,0,n,a,b,1);
    printf("%d\n",ans);
}

int getSumUtil(int *tree, int *lazy, int ss, int se, int qs, int qe, int si)  {
    if(lazy[si] != 0)   {
        int aux = lazy[si];
        lazy[si] = 0;
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
                tree[si] = (se-ss+1) - tree[si];
                break;
        }
        if(ss != se)    {
            if(aux == 1 || aux == 2) {
                lazy[si*2] = aux;
                lazy[si*2+1] = aux;
            }
            if(aux == 3)    {
                if(lazy[si*2] != 0) {
                    int aux3 = lazy[si*2];
                    if(aux3 == 1 || aux3 == 2)
                        aux3 == 1 ? lazy[si*2] = 2 : lazy[si*2] = 1;
                    else
                        lazy[si*2] = 0;
                }
                else
                    lazy[si*2] = aux;
                if(lazy[si*2+1] != 0) {
                    int aux3 = lazy[si*2+1];
                    if(aux3 == 1 || aux3 == 2)
                        aux3 == 1 ? lazy[si*2+1] = 2 : lazy[si*2+1] = 1;
                    else
                        lazy[si*2+1] = 0;
                }
                else
                    lazy[si*2+1] = aux;
            }
        }
    }
    
    if(ss>se || ss>qe || se<qs)
        return 0;
    if(ss>=qs && se<=qe)
        return tree[si];
    int mid = (ss+se)>>1;

    return getSumUtil(tree,lazy,ss,mid,qs,qe,2*si) + getSumUtil(tree,lazy,mid+1,se,qs,qe,2*si+1);
}

void updateRangeUtil(int *tree, int *lazy, int si, int ss, int se, int us, int ue, int dif)   {
    if(lazy[si] != 0)   {
        int aux = lazy[si];
        lazy[si] = 0;
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
                tree[si] = (se-ss+1) - tree[si];
                break;
        }
        if(ss != se)    {
            if(aux == 1 || aux == 2) {
                lazy[si*2] = aux;
                lazy[si*2+1] = aux;
            }
            if(aux == 3)    {
                if(lazy[si*2] != 0) {
                    int aux3 = lazy[si*2];
                    if(aux3 == 1 || aux3 == 2)
                        aux3 == 1 ? lazy[si*2] = 2 : lazy[si*2] =1;
                    else
                        lazy[si*2] = 0;
                }
                else
                    lazy[si*2] = aux;
                if(lazy[si*2+1] != 0) {
                    int aux3 = lazy[si*2+1];
                    if(aux3 == 1 || aux3 == 2)
                        aux3 == 1 ? lazy[si*2+1] = 2 : lazy[si*2+1] =1;
                    else
                        lazy[si*2+1] = 0;
                }
                else
                    lazy[si*2+1] = aux;
            }
        }
    }
    
    if(ss>se || ss>ue || se<us)
        return;
    if(ss>=us && se<=ue)    {
        switch(dif)    {
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
                tree[si] = (se-ss+1) - tree[si];
                break;
        }
        if(ss != se)    {
            if(dif == 1 || dif == 2) {
                lazy[si*2] = dif;
                lazy[si*2+1] = dif;
            }
            if(dif == 3)    {
                if(lazy[si*2] != 0) {
                    int aux3 = lazy[si*2];
                    if(aux3 == 1 || aux3 == 2)
                        aux3 == 1 ? lazy[si*2] = 2 : lazy[si*2] = 1;
                    else
                        lazy[si*2] = 0;
                }
                else
                    lazy[si*2] = dif;
                if(lazy[si*2+1] != 0) {
                    int aux3 = lazy[si*2+1];
                    if(aux3 == 1 || aux3 == 2)
                        aux3 == 1 ? lazy[si*2+1] = 2 : lazy[si*2+1] = 1;
                    else
                        lazy[si*2+1] = 0;
                }
                else
                    lazy[si*2+1] = dif;
            }
        }
        return;
    }
    int mid = (ss+se)>>1;
    updateRangeUtil(tree,lazy,si*2,ss,mid,us,ue,dif);
    updateRangeUtil(tree,lazy,si*2+1,mid+1,se,us,ue,dif);
    tree[si] = tree[si*2] + tree[si*2+1];
}

void construyeST(int *t, vector<int> &A, int pos, int a, int b) {
    if(a == b)
        t[pos] = A[a];
    else   {
        int mid = (a+b)>>1;
        construyeST(t, A, 2*pos, a, mid);
        construyeST(t, A, 2*pos+1,mid+1, b);
        t[pos] = t[2*pos] + t[2*pos+1];
    }
}
