#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

using namespace std;

int main()  {
    int t,n;
    unsigned long long ans;
    while(cin>>t && t)    {
        n = t-1960;
        n /= 10;
        n += 2;
        ans = 1;
        for(int i=0; i<n; i++)
            ans *= 2;
        double cota=ans*log(2);
        double fact=0;
        unsigned long long cont=0;
        for(unsigned long long i=1; i<=ans; i++) {
            fact += log(i);
            if(fact>=cota) {
                cont=i-1;
                break;
            }
        }
        cout<<cont<<"\n";
    }
    return 0;
}
