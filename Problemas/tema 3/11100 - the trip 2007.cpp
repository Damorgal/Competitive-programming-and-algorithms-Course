#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <cmath>
#include <algorithm>

using namespace std;

int main() {
    int n;
    while(cin>>n)   {
        int *bolsa=(int*)calloc(100000,sizeof(int));
        for(int i=0; i<n; i++)
            cin>>bolsa[i];
        sort(bolsa,bolsa+n);
        int tam=-1,cont=1;
        for(int i=0; i<n; i++)    {
            if(bolsa[i]==bolsa[i+1])    {
                cont++;
                continue;
            }
            if(cont>tam)
                tam=cont;
            cont=1;
        }
        printf("%d\n",tam);
        for (int i=0; i<tam; i++)  {
            bool primero=true;
            for (int j=i; j<n; j+=tam) {
                if(primero)
                    primero=false;
                else
                    printf(" ");
                printf("%d",bolsa[j]);
            }
            printf("\n");
        }
        free(bolsa);
    }
    return 0;
}
