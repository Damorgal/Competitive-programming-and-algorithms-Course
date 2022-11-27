#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

using namespace std;

int main() {
    int a,b,v,A,s;
    double contH=0, contV=0;
    while(scanf("%d%d%d%d%d",&a,&b,&v,&A,&s))    {
        if(a==0 && b==0 && v==0 && A==0 && s==0)
            break;
        double x,y;
        x = cos((double)A*3.1415926535/180);
        y = sin((double)A*3.1415926535/180);
        contH = (double)a/2;
        contV = (double)b/2;
        contH += ((double)v*s - (double)v*s/2)*x;
        contV += ((double)v*s - (double)v*s/2)*y;
        printf("%d %d\n",(int)contH/a,(int)contV/b);
    }
    return 0;
}
