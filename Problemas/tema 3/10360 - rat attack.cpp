#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <cmath>

using namespace std;

#define tipo int

tipo **pide_memoria0(int r, int c)    {
    tipo *aux = (tipo*)calloc(r*c,sizeof(tipo));
    tipo **mat = (tipo**)calloc(r,sizeof(tipo*));
    for(int i=0; i<r; i++)  {
        mat[i] = aux+i*c;
    }
    return mat;
}

void libera_memoria(tipo **mat)  {
    free(mat[0]);
    free(mat);
}

int main() {
    ios::sync_with_stdio(false);
    int K;
    scanf("%d",&K);
    for(int k=0; k<K; k++)  {
        int **mat = pide_memoria0(1025,1025);
        int d,n;
        scanf("%d%d",&d,&n);
        int x,y,costo;
        for(int i=0; i<n; i++)   {
            scanf("%d %d %d",&x,&y,&costo);
            for(int j=max(0,x-d); j<=min(x+d,1024); j++)
                for(int k=max(0,y-d); k<=min(y+d,1024); k++)
                    mat[j][k] += costo;
        }
        int resX, resY, maxi = -1;
        for(int i=0; i<1025; i++)    {
            for(int j=0; j<1025; j++)    {
                if(maxi < mat[i][j])   {
                    maxi = mat[i][j];
                    resX = i;
                    resY = j;
                }
            }
        }
        printf("%d %d %d\n",resX,resY,maxi);
        libera_memoria(mat);
    }
    return 0;
}
