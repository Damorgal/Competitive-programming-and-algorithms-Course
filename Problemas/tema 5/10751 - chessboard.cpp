#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

using namespace std;

int main() {
    int t,n;
    scanf("%d",&t);
    while(t--)  {
        scanf("%d",&n);
        double ans=0;
        if(n==0 || n==1)
            ans=0;
        else if(n==2)
            ans=4;
        else    {
            ans = sqrt(2)*(n-2)*(n-2);
            ans += n*n - (n-2)*(n-2);
        }
        printf("%.3f\n\n",ans);
    }
    return 0;
}
