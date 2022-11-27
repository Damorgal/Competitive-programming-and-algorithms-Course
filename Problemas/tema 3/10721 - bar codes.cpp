#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <cmath>

#define tipo long long

using namespace std;

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
    int n,k,m;
    while(scanf("%d %d %d", &n, &k, &m) == 3)   {
        tipo ** dp = pide_memoria0(k+1,n+1);
        dp[0][0]=1;
        for(int i=1; i<=k; i++)
            for(int j=1; j<=n; j++) {
                for(int l=1; l<=m; l++)
                    if(j-l >= 0)
                        dp[i][j] += dp[i-1][j-l];
            }

        printf("%lld\n", dp[k][n]);
        libera_memoria(dp);
    }
    return 0;
}
