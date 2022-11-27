#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

using namespace std;

int main() {
    int n,k;
    while(scanf("%d %d",&n,&k)==2)    {
        int num=1,den=n;
        int num2=0,den2=1;
        int auxnum,auxden,K;
        while(--k)  {
            K = (n+den2) / den;
            auxnum = K*num - num2;
            auxden = K*den - den2;
            num2 = num;
            den2 = den;
            num = auxnum;
            den = auxden;
        }
        printf("%d/%d\n",num,den);
    }
    return 0;
}
