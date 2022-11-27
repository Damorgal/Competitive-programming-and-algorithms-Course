#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <cmath>

using namespace std;

long x,y,n,c1,n1,c2,n2;

void euc_extendido(long a, long b, long &d, long &x, long &y)  {
    if(b == 0) {
        x = 1;
        y = 0;
        d = a;
        return;
    }
    long x1,y1;
    euc_extendido(b,a%b,d,x1,y1);
    x = y1;
    y = x1 - (a/b)*y1;
}

bool verifica()    {
    long g,m1,m2;
    euc_extendido(n1,n2,g,m1,m2);
    if(n%g != 0)
        return false;

    m1 *= n/g;
    m2 *= n/g;
    n2 /= g;
    n1 /= g;
    long c = ceil(-(double)m1/n2);
    long f = floor((double)m2/n1);
    if(c>f)
        return false;
    long precio = c1*n2 - c2*n1;
    if(precio*c < precio*f)    {
        x = m1 + n2*c;
        y = m2 - n1*c;
    }
    else    {
        x = m1 + n2*f;
        y = m2 - n1*f;
    }
    return true;
}

int main()  {
    ios::sync_with_stdio(false);
    while(scanf("%ld",&n) != EOF && n!=0)   {
        scanf("%ld%ld%ld%ld",&c1,&n1,&c2,&n2);
        if(verifica())
            printf("%ld %ld\n",x,y);
        else
            printf("failed\n");
    }
    return 0;
}
