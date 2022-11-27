#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

using namespace std;

int main()  {
    int caso=1,t,n;
    int *cont;
    scanf("%d",&t);
    while(t--){
        scanf("%d",&n);
        cont = (int*)calloc(200,sizeof(int));
        int aux;
        for(int i=0; i<n; i++)  {
            for(int j=0; j<n; j++)  {
                scanf("%d",&aux);
                cont[aux]++;
            }
        }
        int ind=0;
        for(int i=0; i<=100; i++)
            if(cont[i]>n)
                ind = 1;
        printf("Case %d: ",caso++);
        if(ind)
            printf("no\n");
        else
            printf("yes\n");
        free(cont);
    }
    return 0;
}
