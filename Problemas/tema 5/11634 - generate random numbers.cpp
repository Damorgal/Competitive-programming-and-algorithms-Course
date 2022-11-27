#include <iostream>
#include <stdio.h>
#include <cstdlib>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    int n,cont;
    while(scanf("%d",&n)==1 && n)    {
        char m[10000]={};
        for(cont=0; m[n]==0; cont++) {
            m[n] = 1;
            n = n*n;
            n /= 100;
            n = n%10000;
        }
        printf("%d\n",cont);
    }
    return 0;
}
