#include <stdlib.h>
#include <cmath>
#include <iostream>

using namespace std;

int** createSparseTable(int *v, int N)    {
    int difMax=N, logN=0;
    // logN = ceil(log2(N))
    while(difMax >>=1) logN++;
    if(1<<logN < N) logN++;
    
    // Memoria para la sparse table
    int **ST = (int**)malloc(N*sizeof(int*));
    if(ST == NULL) return NULL;
    ST[0] = (int*)malloc(N*logN*sizeof(int));
    if(ST[0] == NULL) return NULL;
    for(int t=1; t<N; t++)
        ST[t] = ST[t-1] + logN;
    
    // Llenado de tabla 
    for(int j=1; j<logN; j++)   {
        for(int i=0; i<N; i++)  {
            // Dif. max de long. 1
            //if(j==0)
              //  ST[i][j]=0;
            // Dif. max de long. 2
            if(j==1)   
                i+1<N ? ST[i][j]=v[i+1]-v[i] : ST[i][j]=-1;
            // Dif. max. de long mayor
            else    {
                //if(i+pow(2,j)<=N)   {
                if(i+(1<<j)<=N)   {
                    difMax = ST[i][j-1];
                    //int aux = i+pow(2,j-1);
                    int aux = j==1? 1: i+(1<<(j-1));
                    if(difMax<ST[aux][j-1])
                        difMax=ST[aux][j-1];
                    if(difMax<v[aux]-v[aux-1])
                        difMax=v[aux]-v[aux-1];
                    ST[i][j]=difMax;
                }
                else
                    //ST[i][j] = -1;
                    break;
            }
        }
    }
    return ST;
}

int binarySearch(int *v, int a, int b, int N, int t) {
    if(a == b)
        return a;
    //int m = floor((float)(a+b)/2.0);
    int m = (a+b)>>1;
    if(m+1 < N) {
        if(v[m]<=t && v[m+1]>t)
            return m;
        else if(v[m]<=t)
            return binarySearch(v,m+1,b,N,t);
        else 
            return binarySearch(v,a,m,N,t);
    }
    else 
        return m;
}

void binarySearch(int **ST, int a, int k, int d)   {
    if(a == k)  
        printf("%d\n",a+1);
    else    {
        int dist, difMax, i=(a+k)>>1;
        dist = k-i+1;
        //aux = floor(log2(dist));
        int aux = 0;
        while(dist >>= 1) aux++;
        //ST[i][aux]<ST[k-(int)pow(2,aux)+1][aux] ? difMax=ST[k-(int)pow(2,aux)+1][aux] : difMax=ST[i][aux];
        ST[i][aux]<ST[k-(1<<aux)+1][aux] ? difMax=ST[k-(1<<aux)+1][aux] : difMax=ST[i][aux];
        if(difMax <= d)
            binarySearch(ST,a,i,d);
        else    
            binarySearch(ST,i+1,k,d);
    }
}

int main()  {
    int N, m, t, d, *vec, **ST;
    scanf("%d",&N);
    // Memoria para el arreglo
    vec = (int*)malloc(N*sizeof(int));
    // Leemos el arreglo
    for(t=0; t<N; scanf("%d", &vec[t++]));
    // Creamos sparse table de maximos
    ST = createSparseTable(vec,N);
    scanf("%d",&m);
    while(m--)  {
        scanf("%d %d",&t,&d);
        int k = binarySearch(vec,0,N-1,N,t);
        binarySearch(ST,0,k,d);
    }
    free(vec);
    free(ST[0]);
    free(ST);
}
