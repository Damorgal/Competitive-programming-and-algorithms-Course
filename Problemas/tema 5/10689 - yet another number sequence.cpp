#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

using namespace std;

int main() {
    int t,a,b,n,m;
    scanf("%d",&t);
    while(t--)  {
        int aux,digitos;
        scanf("%d%d%d%d",&a,&b,&n,&m);
        switch(m)   {
            case 4:
                digitos=10000;
                aux=15000;
                break;
            case 3:
                digitos=1000;
                aux=1500;
                break;
            case 2:
                digitos=100;
                aux=300;
                break;
            case 1:
                digitos=10;
                aux=60;
                break;
        }
        int *vec = (int*)malloc(aux*sizeof(int));
        vec[0]=a%digitos;
        vec[1]=b%digitos;
        for(int i=2; i<aux; i++)
            vec[i]=(vec[i-1]+vec[i-2])%digitos;
        printf("%d\n",vec[n%aux]);
        free(vec);
    }
    return 0;
}
