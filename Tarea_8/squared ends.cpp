#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

using namespace std;

#define inf 10000000

int main()  {
    int N, K;
    cin>>N; cin>>K;
    int *vec = (int*)malloc(N*sizeof(int));
    int DP[101][100000];
    for(int i=0; i<N; i++)
        scanf("%d",&vec[i]);
    // Realizamos el algoritmo
    int ans;
    for(int i=1; i<=K; i++)  {
        if(i==1)    {
            for(int j=0; j<N; j++)
                DP[i][j] = (int)pow((float)vec[0]-vec[j],2);
            ans = DP[i][N-1];
        }
        else    {
            for(int j=i; j<N; j++)  {
                int min = inf;
                for(int k=i; k<=j; k++)
                    if(DP[i-1][k-1]+(int)pow((float)vec[k]-vec[j],2) < min)
                        min = DP[i-1][k-1]+(int)pow((float)vec[k]-vec[j],2);
                    DP[i][j] = min;
                }
            }
            ans = DP[i][N-1];
        }
    printf("%d",ans);
    free(vec);
    return 0;
}