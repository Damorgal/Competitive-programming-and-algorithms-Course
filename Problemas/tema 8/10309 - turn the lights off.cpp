#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <cmath>
#include <string>

#define tam 10

using namespace std;

unsigned int focos[tam];
int cont=0;

void cambia(int r, int c)  {
    if(c==0)
        focos[r]=focos[r]^3u;
    else
        focos[r]=(focos[r]^(7u<<(c-1))) & ((1u<<tam)-1);
    if(r+1<tam)
        focos[r+1]=focos[r+1]^(1u<<c);
    cont++;
}

int main() {
    string nombre;
    while(cin>>nombre && nombre!="end") {
        for(int i=0; i<tam; i++)    {
            string aux;
            cin>>aux;
            focos[i]=0;
            for(int j=0; j<tam; j++)    {
                if(aux[j]=='O')
                    focos[i]=focos[i] | (1u<<j);
            }
        }
        int best=101;
        for(uint r=0; r<(1u<<tam); r++) {
            cont=0;
            uint t[tam];
            for(int i=0; i<tam; i++)
                t[i]=focos[i];
            for(int i=0; i<tam; i++)    {
                if(r&(1u<<i))
                    cambia(0,i);
            }
            for(int i=1; i<tam; i++)    {
                for (int j=0; j<tam; j++)   {
                    if(focos[i - 1]&(1u<<j))
                        cambia(i,j);
                }
            }
            if(focos[tam-1]==0)
                best=min(best,cont);
            swap(t,focos);
        }
        if(best==101)
            best=-1;
        cout<<nombre;
        printf(" %d\n",best);
    }
    return 0;
}
