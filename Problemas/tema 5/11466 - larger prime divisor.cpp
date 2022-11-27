#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <cmath>
#include <bitset>
#include <vector>

#define inf 10000000

using namespace std;

long long tam_primo;
vector<int> vec;
bitset<10000010> bits;

void primo(long long upperbound)    {
    tam_primo = upperbound+1;
    bits.set();
    bits[0]=bits[1]=0;
    for(long long i=2; i<=tam_primo; i++)
        if(bits[i])   {
            for(long long j=i*i; j<=tam_primo; j+=i)
                bits[j] = 0;
            vec.push_back((int)i);
        }
}

int main() {
    ios::sync_with_stdio(false);
    primo(inf);
    long long n;
    while(cin>>n && n)  {
        if(n<0)
            n *= -1;
        if(n<=inf && bits[n]==1)
            cout<<"-1\n";
        else    {
            int cont=0;
            long long ans=-1;
            for(int i=0; vec[i]<=sqrt(n) && i<tam_primo; i++)    {
                if(n%vec[i] == 0)    {
                    ans = vec[i];
                    cont++;
                    while(n%vec[i] == 0)
                        n /= vec[i];
                }
            }
            if(n!=1)  {
                ans=n;
                cont++;
            }
            if(cont<=1)
                ans=-1;
            cout<<ans<<endl;
        }
    }
    return 0;
}
