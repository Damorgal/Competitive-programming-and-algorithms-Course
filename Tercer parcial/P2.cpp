#include <iostream>
#include <vector>
#include <string.h>
#include <cmath>

using namespace std;

void llenaCriba_mod4(bool* criba, int N)   {
    memset(criba,1,N*sizeof(bool));
    criba[0] = criba[1] = 0;
    int sq = sqrt(N)+1;
    for(long long int i=2; i<sq; i++)
        if(criba[i])    {
            for(long long j=2*i; j<N; j+=i)
                criba[j] = 0;
        }
}

// resolveremos observando que los cuadrados son congruentes a 0 o 1 mod 4
// Por tanto a^2+b^4 es congruentes a 0, 1 o 2 modulo 4
// Pero un primo no puede ser congruente a 0, ni 2 (mas que el 2) modulo 4
// Porque implicaria que dicho primo es par
// Así buscamos a los primos tales que son congruentes 1 mod 4
int solve(int N)    {
    // obtenemos primos posibles
    bool criba[N+1];
    llenaCriba_mod4(criba, N+1);
    // Buscamos cuantos cumplen
    int sq2 = sqrt(N)+1;
    int sq4 = sqrt(sqrt(N))+1;
    int cont = 0;
    for(int i=1; i<sq4; i++)    {
        for(int j=1; j<sq2; j++)    {
            int p = j*j+i*i*i*i;
            if(p <= N)
                if(criba[p])  { 
                    cont++;
                    // Lo tachamos para no contarlo dos veces
                    criba[p] = 0;
                }
        }
    }
    return cont;
}


int main() {
    ios::sync_with_stdio(false);
    int N;
    cin >> N;
    cout << solve(N) << endl;
    return 0;
}
