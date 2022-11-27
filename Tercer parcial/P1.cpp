#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

bool* multiplos;

inline int gcd(int a, int b)    {
    if (a == 0)
        return b;
    return gcd(b%a, a);
}

// Busca el primer indice que tiene v1 numeros posibles consecutivos en intervalo a b
unsigned int  v1_consecutivos(unsigned int a, unsigned int b, unsigned int v1)   {
    for(unsigned int i=a; i<b-v1+1; i++)    {
        bool ind = 0;
        for(unsigned int j=i; j<i+v1; j++)    {
            // Salimos si hay uno no posible
            if(multiplos[j] == 0)   {
                ind = 1;
                break;
            }
        }
        // Si todos fueron posibles
        if(ind == 0)    
            return i;
    }
    return 0;
}

unsigned int llena(unsigned int v1, unsigned int v2)    {
    // LLenamos multipllos de v1 y v2
    multiplos = (bool*)calloc(1000000000,sizeof(bool));
    unsigned int min_pos = 1000000000;
    for(unsigned int j=0; j<v2*v1; j+=v2) {
        for(unsigned int i=0; i<v2; i++)   {
            // Lo marcamos como que es posible llegar a el
            multiplos[i*v1 + j] = 1;
            // Checamos si tenemos v1 consecutivos
            unsigned int pos = v1_consecutivos(i*v1+j-v1+1, i*v1+j+v1-1, v1);
            // Si si, lo guardamos como posible minimo
            if(pos != 0)    {
                if(pos < min_pos)
                    min_pos = pos;
                break;
            }
        }
    }
    free(multiplos);
    return min_pos;
}

unsigned int solve(unsigned int v1, unsigned int v2)    {
    // v2 será el mayor entero
    if(v1 > v2)
        swap(v1,v2);
    if(v1 == 2)
        return v2-1;
    // Para v1 > 2 necesitamos tener v1 enteros consecutivos posibles de formar para obtener asi cualquier numero
    return llena(v1,v2);
}

int main() {
    ios::sync_with_stdio(false);
    unsigned int v1,v2;
    cin >> v1 >> v2;
    if(gcd(v1,v2) == 1)
        cout << solve(v1,v2) << endl;
    else
        cout << "-1" << endl;
    return 0;
}
