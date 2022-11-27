#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <math.h>

using namespace std;

long long H(int n)  {
    long long res=0;
    if(n==0)
        return 0;
    int a=1;
    int b=(int)floor(sqrt(n));
    if(b*b==n)  {
        res += n/b;
        b--;
    }
    for(; a<=b; a++)    {
        res += n/a;
        res += max(0,n/a - b);
    }
    return res;
}

int main()  {
    int n,t;
    cin>>t;
    while(t--)    {
        cin>>n;
        cout<<H(n)<<"\n";
    }
    return 0;
}
