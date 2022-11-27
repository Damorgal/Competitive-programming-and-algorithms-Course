#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

using namespace std;

int main() {
    int n,t,suma;
    while(scanf("%d",&suma) && suma!=-1)    {
        for(n=(int)sqrt(2*suma); n>0; n--) {
            int aux=2*suma;
            aux += n-n*n;
            if(aux%(2*n)==0) {
                t=aux/(2*n);
                break;
            }
        }
        printf("%d = %d + ... + %d\n",suma,t,t+n-1);
    }
    return 0;
}