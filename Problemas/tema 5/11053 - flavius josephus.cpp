#include <iostream>
#include <stdio.h>
#include <cstdlib>

using namespace std;

int main()  {
    ios::sync_with_stdio(false);
    int n,a,b;
    while(cin>>n && n>0)    {
        cin>>a>>b;
        unsigned long long lm=0;
        unsigned long long lm2=0;
        while(1)    {
            lm = (lm*lm)%n;
            lm = (a*lm+b)%n;
            lm2 = (lm2*lm2)%n;
            lm2 = (a*lm2+b)%n;
            lm2 = (lm2*lm2)%n;
            lm2 = (a*lm2+b)%n;
            if(lm==lm2)
                break;
        }
        lm2 = 0;
        while(1)    {
            lm = (lm*lm)%n;
            lm = (a*lm+b)%n;
            lm2 = (lm2*lm2)%n;
            lm2 = (a*lm2+b)%n;
            if(lm==lm2)
                break;
        }
        unsigned long long aux=lm2;
        unsigned long long mu=0;
        while(1)    {
            lm2 =(lm2*lm2)%n;
            lm2 = (a*lm2+b)%n;
            mu++;
            if(aux==lm2)
                break;
        }
        cout<<(n-mu)<<endl;
    }
    return 0;
}
