#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iterator>
#include <map>
#include <vector>
#include <string>

using namespace std;

int *despiertos;

int main() {
    ios::sync_with_stdio(false);
    int n,m;
    string wakeup;

    while(cin>>n)  {
        despiertos = (int*)calloc(n+1,sizeof(int));
        cin>>m;
        cin>>wakeup;

        vector<string> con;
        map<char,int> mapa;
        int x=0;
        for(int j=0; j<3; j++)
            if(mapa.find(wakeup[j]) == mapa.end())  {
                mapa[wakeup[j]] = x;
                x++;
            }
        for(int i=0; i<m; i++)  {
            string aux;
            cin>>aux;
            con.push_back(aux);
            if(mapa.find(aux[0])==mapa.end())   {
                mapa[aux[0]] = x;
                x++;
            }
            if(mapa.find(aux[1])==mapa.end())   {
                mapa[aux[1]] = x;
                x++;
            }
        }
        if(n > mapa.size())   {
            printf("THIS BRAIN NEVER WAKES UP\n");
            continue;
        }
        for(int i=0; i<3; i++)
            despiertos[mapa[wakeup[i]]] = 1;

        int cont=3;
        int years=0;
        while(cont < n) {
            vector<int> pendientes;
            for(map<char,int>::iterator it = mapa.begin(); it!=mapa.end(); it++)    {
                int j = it->second;
                if(despiertos[j] == 1)
                    continue;

                int cont2=0;
                for(int k=0; k<con.size(); k++) {
                    if(mapa[con[k][0]]==j && despiertos[mapa[con[k][1]]]==1)
                        cont2++;
                    else
                        if(mapa[con[k][1]]==j && despiertos[mapa[con[k][0]]]==1)
                        cont2++;
                }
                if(cont2>=3)
                    pendientes.push_back(j);
            }

            cont += pendientes.size();
            if(pendientes.empty())
                break;
            for(int j=0; j<pendientes.size(); j++)
                despiertos[pendientes[j]] = 1;
            years++;
        }
        if(cont < n)
            printf("THIS BRAIN NEVER WAKES UP\n");
        else
            printf("WAKE UP IN, %d, YEARS\n",years);
        free(despiertos);
    }
    return 0;
}
