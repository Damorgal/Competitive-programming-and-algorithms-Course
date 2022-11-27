#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

using namespace std;

int main()  {
    unsigned long long n,cont;
    while(cin>>n && n>=3)    {
        cont=0;
        for(int i=1; i+i+1<n; i++)   {
            int j=i+1;
            cont += (n-(i+j))*(n-(i+j)+1)/2;
        }
        cout<<cont<<endl;
    }
    return 0;
}