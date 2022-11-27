#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <cmath>
#include <string>
#include <cstring>

#define inf 1000000000

using namespace std;

const int tam=27;
int n=26,dY[tam][tam],dM[tam][tam];
int tY,tM;

void construye(int m)   {
    char calle,dir,u,v;
    int constru;
    while(m--)  {
        cin>>calle>>dir>>u>>v>>constru;
        int x=u-'A';
        int y=v-'A';
        if(calle == 'Y')   {
            if(dir == 'U')
                dY[x][y]=constru;
            else
                dY[x][y]=dY[y][x]=constru;
        }
        else    {
            if(dir == 'U')
                dM[x][y]=constru;
            else
                dM[x][y]=dM[y][x]=constru;
        }
    }
    for(int i=0; i<n; i++)
        dM[i][i] = dY[i][i]=0;
    cin>>u>>v;
    tY = u-'A';
    tM = v-'A';
}

int main()  {
    int K;
    while(cin>>K)   {
        if(K==0)
            break ;
        int i,j,k;
        for(int i=0; i<n; i++)  {
            for(int j=0; j<n; j++)
                dY[i][j]=dM[i][j]=inf;
            dY[i][i]=dM[i][i]=0;
        }
        construye(K);

        for(int k=0; k<n; k++)
            for(int i=0; i<n; i++)
                for(int j=0; j<n; j++)  {
                    if(dY[i][j] > dY[i][k]+dY[k][j])    {
                        dY[i][j] = dY[i][k]+dY[k][j];
                    }
                    if(dM[i][j] > dM[i][k]+dM[k][j]) {
                        dM[i][j] = dM[i][k]+dM[k][j];
                    }
                }
        int ans=inf;
        for(int i=0; i<n; i++)  {
            if(dY[tY][i]==inf || dM[tM][i]==inf)
                continue;
            if(dY[tY][i]+dM[tM][i] < ans)
                ans = dY[tY][i]+dM[tM][i];
        }
        if(ans==inf)
            printf("You will never meet.\n");
        else    {
            printf("%d",ans);
            for(int i=0; i<n; i++)
                if(dY[tY][i]+dM[tM][i] == ans)
                    printf(" %c",i+'A');
            printf("\n");
        }
    }
    return 0;
}
