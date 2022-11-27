#include <iostream>
#include <stdio.h>


using namespace std;

int main()  {
    int S, B, r, l;
    int I[100001];
    int D[100001];
    while(1)    {
        scanf("%d %d",&S,&B);
        if(S == 0 && B == 0)
            break;
        for(int i = 1; i<=S; i++)   {
            I[i] = i-1;
            D[i] = i+1;
        }
        I[1] = D[S] = 0;
        for(int i=0; i<B; i++)  {
            scanf("%d",&l);
            scanf("%d",&r);
            I[D[r]] = I[l];
            if(I[l] == 0)
                printf("* ");
            else
                printf("%d ",I[l]);

            D[I[l]] = D[r];
            if(D[r] == 0)
                printf("*\n");
            else
                printf("%d\n",D[r]);
        }
        printf("-\n");
    }
    return 0;
}
