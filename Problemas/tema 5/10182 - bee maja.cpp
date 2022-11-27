#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

using namespace std;

int main()  {
    int n,cont,maja,x,y;
    while(cin>>n){
        for(cont=0,maja=1; maja<n;)
            maja += 6*(++cont);
        for(x=cont,y=0; maja!=n;){
            for(; maja!=n && y+cont!=0; y--)
                maja--;
            for(; maja!=n && x!=0; x--)
                maja--;
            for(; maja!=n && y!=0; x--,y++)
                maja--;
            for(; maja!=n && y!=cont; y++)
                maja--;
            for(; maja!=n && x!=0; x++)
                maja--;
            for(; maja!=n && x!=cont; x++,y--)
                maja--;
        }
        printf("%d %d\n",x,y);
    }
    return 0;
}
