#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

using namespace std;

int main()  {
    int caso=1,n;
    while(1)    {
        scanf("%d",&n);
        if(n==0) 
            break;
        printf("Case %d: %d\n",caso++,n>>1);
    }
    return 0;
}
