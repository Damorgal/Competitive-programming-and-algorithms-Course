#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

using namespace std;

int main() {
    unsigned long long n,m,c;
    while(cin>>n>>m>>c) {
        if(n==0 && m==0 && c==0)
            break;
        unsigned long long aux;
        if(c==0)
            aux=(n-7)*(m-7)/2;
        else
            aux=((n-7)*(m-7)+1)/2;
        printf("%lld\n",aux);
    }
    return 0;
}
