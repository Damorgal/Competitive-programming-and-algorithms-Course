#include <iostream>
#include <stdio.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    int t,n,caso=1;
    int A[100001];

    scanf("%d",&t);
    while(t--)  {
        scanf("%d",&n);
        for(int i=1; i<=n; i++)
            scanf("%d",&A[i]);

        int k=0,aux;
        //Mayor salto
        for(int i=1; i<=n; i++) {
            if(A[i]-A[i-1] > k)
                k = A[i]-A[i-1];
        }
        aux = k;
        for(int i=1; i<=n; i++) {
            if(A[i]-A[i-1] == k)
                k--;
            else if(A[i]-A[i-1] > k)    {
                aux++;
                break;
            }
        }
        printf("Case %d: %d\n",caso,aux);
        caso++;
    }
    return 0;
}
