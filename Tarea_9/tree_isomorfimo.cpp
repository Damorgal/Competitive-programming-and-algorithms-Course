#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <algorithm>

using namespace std;

int **pide_memoria0(int r, int c)    {
    int *aux = (int*)calloc(r*c,sizeof(int));
    int **mat = (int**)malloc(r*sizeof(int*));
    for(int i=0; i<r; i++)
        mat[i] = aux + i*c;
    return mat;
}

void libera_memoria(int **m) {
    free(m[0]);
    free(m);
}

void datos(int **t, int **data, int n, int pos, int level)    {
    //Renglon de data equivale al nivel en el arbol
    //Columna de data al numero de vertice
    //Lo que guarda en la posicion es el grado del vertice
    data[level][pos]=0;
    for(int i=1; i<=n; i++)    {
       if(t[pos][i])    {
            t[i][pos]=0;
            data[level][pos]++;
            datos(t,data,n,i,level+1);
            t[i][pos]=1;
       }
    }
}

bool isomorfismo(int **t, int **data, int N, int pos)    {
    int **data2 = pide_memoria0(N+1,N+1);
    datos(t,data2,N,pos,1);
    for(int i=1; i<=N; i++) {
        vector<int> comp1,comp2;
        for(int j=1; j<=N; j++) {
            if(data[i][j] != 0)
                comp1.push_back(data[i][j]);
            if(data2[i][j] != 0)
                comp2.push_back(data2[i][j]);
        }
        if(comp1.size() != comp2.size())
            return false;
        sort(comp1.begin(),comp1.begin()+comp1.size());
        sort(comp2.begin(),comp2.begin()+comp2.size());
        for(int j=0; j<comp1.size(); j++)
            if(comp1[j] != comp2[j])
                return false;
    }

    return true;
}

int main()  {
    int N,K;
    scanf("%d",&K);
    while(K--)  {
        scanf("%d",&N);
        int **t1 = pide_memoria0(N+1,N+1);
        int **t2 = pide_memoria0(N+1,N+1);
        int a,b;
        //Leemos los datos
        for(int i=1; i<N; i++)  {
            scanf("%d %d",&a,&b);
            t1[a][b]=t1[b][a]=1;
        }
        for(int i=1; i<N; i++)  {
            scanf("%d %d",&a,&b);
            t2[a][b]=t2[b][a]=1;
        }
        // La raiz del arbol 1 sera el vertice 1 y compararemos con cualquier nodo del arbol 2

        //Renglon de data equivale al nivel en el arbol
        //Columna de data al numero de vertice
        //Lo que guarda en la posicion es el grado del vertice
        int **data = pide_memoria0(N+1,N+1);
        bool ind=false;
        for(int i=1; i<N; i++)  {
            datos(t1,data,N,1,1);
            if(isomorfismo(t2,data,N,i))    {
                ind=true;
                break;
            }
        }
        if(ind)
            printf("YES\n");
        else
            printf("NO\n");

        libera_memoria(data);
        libera_memoria(t1);
        libera_memoria(t2);
    }
    return 0;
}
