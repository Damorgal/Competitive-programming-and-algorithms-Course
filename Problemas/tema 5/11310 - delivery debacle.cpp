#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

using namespace std;

int main()  {
    int t,k;
    unsigned long long n=0,n2=0,n3=0;
    cin>>t;
    while(t--)    {
        cin>>k;
        for(int i=0; i<k; i++)   {
            if(i>2) {
                unsigned long long aux=n;
                n += n2*4 + n3*2;
                n3=n2;
                n2=aux;
            }
            else if(i==0)
                n=1;
            else if(i==1)   {
                n=5;
                n2=1;
            }
            else if(i==2)   {
                n=11;
                n2=5;
                n3=1;
            }
        }
        cout<<n<<endl;
    }
    return 0;
}
