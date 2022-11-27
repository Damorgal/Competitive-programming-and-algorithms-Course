#include <iostream>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <algorithm>

using namespace std;

#define N 10000009
#define llong long long
bool criba[N];

// Computes b^e mod md
llong modPow(llong b,llong e,llong md) {
    llong rm = 1;
    llong bb = b%md;
    while (e) {
        if (e%2)
            rm = (rm * bb)%md;
        e >>= 1;
        bb = (bb*bb)%md;
    }
    return rm;
}
bool isProbablePrime(llong n, int c) {
    if (n < 2 || (n%2==0))
        return false;
    if (n == 2)
        return true;
    // Writes n-1 = 2^s d with d odd
    llong d = n-1;
    int s = 0;
    while (d%2==0) {
        d >>= 1;
        s++;
    }
    llong b;
    // Performs c tests
    for (int k = 0; k< c; k++) {
        // Random x in [2,n-2]
        llong x = 2 + rand()%(n-3);
        b = modPow(x, d, n);
        // Inconclusive test
        if ((b == 1) || (b == n-1))
            continue;
        for (int i = 1; i < s; i++) {
            b = (b*b)%n;
            if (b == n-1)
                break;
        }
        // If we did not find -1 in the loop, we return false
        if (b != n-1)
            return false;
    }
    // Probably prime (all inconclusive tests)
    return true;
}

void llenaCriba()   {
    memset(criba,1,N*sizeof(bool));
    criba[0] = criba[1] = 0;
    for(long long int i=2; i<10000; i++)
        if(criba[i])    {
            for(llong j=2*i; j<N; j+=i)
                criba[j] = 0;
        }
}

bool primoRotacion(llong x)   {
    int v[10],i;
    long long int aux;
    for(i=0; x; i++)    {
        v[i] = x%10;
        x /= 10;
    }
    sort(v, v+i);
    do  { 
        aux = 0;
        for(int j=0; j<i; j++)
            aux += v[j]*(long long int)pow(10,i-1-j);
        if(!isProbablePrime(aux,5))
            return false;
        if(!criba[aux])
            return false;
    } while (next_permutation(v, v+i)); 
    return true;
}

int main()  {
    llenaCriba();
    long long int p,q,cont=0;
    cin >> p >> q;
    for(long long int i=p; i<=q; i++)    {
            if(criba[i])
                if(primoRotacion(i))
                    cont++;
        
    }
    cout << cont << endl;
    return 0;
}
