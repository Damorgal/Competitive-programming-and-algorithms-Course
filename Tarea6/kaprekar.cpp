#include <iostream>
#include <stdlib.h>
#include <vector>
#include <math.h>

using namespace std;

vector<int> convierte(long long int n) {
    vector<int> vec;
    while(1)    {
        vec.push_back((int)n%10);
        n /= 10;
        if(n == 0)
            break;
    }
    int N = ((int)vec.size())/2, aux;
    for(int i=0; i<N; i++)  {
        aux = vec[i];
        vec[i] = vec[((int)vec.size())-1-i];
        vec[((int)vec.size())-1-i] = aux;
    }
    return vec;
}

bool kaprekar(long long int n) {
    vector<int> n2 = convierte(n*n);
    int N = (int)n2.size();
    long long int suma;
    for(int sep=0; sep<N-1; sep++)  {
        int cont=0;
        suma = 0;
        for(int i=sep; i>=0; i--, cont++)
            suma += n2[i]*pow(10,cont);
        cont=0;
        for(int i=N-1; i>sep; i--, cont++)
            suma += n2[i]*pow(10,cont);
        if(suma == n)
            return 1;
    }
    return 0;
}

long long int MayorKaprekar(long long int n)    {
    while(--n)  {
        if(kaprekar(n))
            return n;
    }
    return -1;
}

int main()  {
    long long int n,k;
    n=100;
    k = MayorKaprekar(n);
    cout << "El mayor kaprekar inferior a " << n << " es: "<< k << endl;
    return 0;
}
