#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <cmath>

using namespace std;

int main()  {
    ios::sync_with_stdio(false);
    int t,n,A[1001];
    scanf("%d",&t);
    for(int k=0; k<t; k++)  {
        scanf("%d",&n);
        int ans=0;
        for(int i=0; i<n; i++)  {
            int aux,j;
            scanf("%d",&aux);
            for(j=i-1; j>=0; j--)   {
                if(aux < A[j])
                    A[j+1] = A[j];
                else
                    break;
            }
            A[j+1] = aux;
            ans += j+1;
        }
        printf("%d\n",ans);
    }
    return 0;
}
