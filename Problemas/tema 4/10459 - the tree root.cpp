#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <bitset>

using namespace std;

int n,ind,t,best,worst;
const int tam=5005;
int **hijo,*padre,*tree;
bitset<tam> vec;
vector<int> K[tam];

void dfs(int x) {
    vec[x]=true;
    for(int j=0,J=K[x].size(); j<J; j++)    {
        int y=K[x][j];
        if(!vec[y]) {
            dfs(y);
            hijo[x][1] = max(hijo[x][1],hijo[y][0]+1);
            if(hijo[x][0] < hijo[x][1])
                swap(hijo[x][0],hijo[x][1]);
        }
    }
}

void dfs2(int x, int d) {
    vec[x]=true;
    padre[x]=d;
    for(int j=0,J=K[x].size(); j<J; j++)   {
        int y=K[x][j];
        if(!vec[y])
            dfs2(y,max(d,(hijo[y][0]+1!=hijo[x][0] ? hijo[x][0]:hijo[x][1]))+1);
    }
}

int main() {
    while(cin>>n) {
        for(int i=1; i<=n; i++) {
            cin>>t;
            K[i].resize(t);
            for(ind=0; ind<t; ind++)
                cin>>K[i][ind];
        }
        int *aux=(int*)calloc(tam*2,sizeof(int));
        hijo=(int**)malloc(tam*sizeof(int*));
        for(int i=0; i<tam; i++)
            hijo[i]=aux + 2*i;
        padre=(int*)calloc(tam,sizeof(int));
        tree=(int*)malloc(tam*sizeof(int));
        vec.reset();
        dfs(1);
        vec.reset();
        dfs2(1,0);
        best=2147483647;
        worst=0;
        for(int i=1; i<=n; i++) {
            tree[i]=max(padre[i],max(hijo[i][0],hijo[i][1]));
            best=min(tree[i],best);
            worst=max(tree[i],worst);
        }
        printf("Best Roots  :");
        for(int i=1; i<=n; i++) {
            if(tree[i] == best)
                printf(" %d",i);
        }
        printf("\nWorst Roots :");
        for(int i=1; i<=n; i++) {
            if(tree[i] == worst)
                printf(" %d",i);
        }
        printf("\n");
        free(hijo[0]);
        free(hijo);
        free(padre);
        free(tree);
    }
    return 0;
}
