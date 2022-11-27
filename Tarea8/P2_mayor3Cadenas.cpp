#include <iostream>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <algorithm>

using namespace std;

#define SIZEMAX 100000
int freqs[SIZEMAX];
int suffarray[SIZEMAX];
int rankarray[SIZEMAX];
int tmprankarray[SIZEMAX];
int tmpsuffarray[SIZEMAX];
int phi[SIZEMAX];
int lcp[SIZEMAX];
int plcp[SIZEMAX];

string s;
int n,n1,n2,n3;

void radixSort(int k)   {
    int m = max(300,n);
    memset(&freqs[0], 0, sizeof(freqs));
    for(int i=0; i<n; i++)
    if(i+k < n)
        freqs[rankarray[i+k]]++;
    else
        freqs[0]++;
    // Frecuencias
    int sfs=0;
    for (int i=0; i<m; i++) {
        int freq = freqs[i]; 
        freqs[i] = sfs; 
        sfs += freq;
    }
    // Lugar de los elementos en el arreglo ordenado
    for (int i=0; i<n; i++)
    if(suffarray[i]+k < n)
        tmpsuffarray[freqs[rankarray[suffarray[i]+k]]++] = suffarray[i];
    else
        tmpsuffarray[freqs[0]++] = suffarray[i];
    // Regresamos los elementos ordenados
    for (int i=0; i<n; i++)
        suffarray[i] = tmpsuffarray[i];
}

void buildSuffArray()   {
    for(int i=0; i<n; i++) {
        rankarray[i] = s[i];
    }
    // Inicializacion
    for (int i=0; i<n; i++)
        suffarray[i] = i;
    // Hacerlo log n veces
    for(unsigned int k=1; k<n; k<<=1)   {
        // Ordenar por el k-1 elemento
        radixSort(k);
        // Ordenar por el primer elemento
        radixSort(0);
        // Rankings basados en el ordenamiento
        int r=0;
        tmprankarray[suffarray[0]] = r;
        for(int i=1; i<n; i++)  {
            if(rankarray[suffarray[i]] != rankarray[suffarray[i-1]] || (suffarray[i]+k<n && rankarray[suffarray[i]+k] !=rankarray[suffarray[i-1]+k]))
                r++;
            tmprankarray[suffarray[i]] = r;
        }
        for(int i=0; i<n; i++) {
            // Actualizamos rango
            rankarray[i] = tmprankarray[i];
        }
    }
}

void buildLCP() {
    phi[suffarray[0]] = -1;
    for(int i=1; i<n; i++)
        phi[suffarray[i]] = suffarray[i-1];
    int l = 0;
    for(int i=0; i<n; i++)  {
        if(phi[i] == -1)    { 
            plcp[i] = 0; 
            continue; 
        }
        while(s[i+l] == s[phi[i]+l]) l++;
        plcp[i] = l;
        l = max(l-1, 0);
    }
    for(int i=0; i<n; i++)
        lcp[i] = plcp[suffarray[i]];
}

pair<int,int> lrs() {
    int ind = 0, lcpmax = -1;
    for(int i=1; i<n; i++)
        if(lcp[i] > lcpmax) {
        lcpmax = lcp[i];
        ind = i;
    }
    return make_pair(lcpmax, ind);
}

int owner(int i)    { 
    if(i < n1)
        return 1;
    else if(i>n1 && i<=n2+n1)
        return 2;
    return 3;
}

pair<int,int> lcs() {
    int lcpind = 0, lcpmax = -1;
    for(int i=2; i<s.size(); i++)
        if(owner(suffarray[i]) != owner(suffarray[i-1]) && 
            owner(suffarray[i]) != owner(suffarray[i-2]) && 
             owner(suffarray[i-2]) != owner(suffarray[i-1]) && lcp[i] > lcpmax) {
            lcpmax = lcp[i];
            lcpind = i;
        }
    return make_pair(lcpmax, lcpind);
}

int main()  {
    ios::sync_with_stdio(false);
    string aux,aux2;
    getline(cin,s);
    n1 = s.size();
    s.push_back('.');
    getline(cin,aux);
    n2 = aux.size();
    for(int i=0; i<n2; i++) 
        s.push_back(aux[i]);
    s.push_back(';');
    getline(cin,aux2);
    n3 = aux2.size();
    for(int i=0; i<n3; i++) 
        s.push_back(aux2[i]);
    s.push_back('$');
    n = s.size();
    buildSuffArray();
    buildLCP();
    pair<int,int> ans = lcs();
    
    if(ans.first <= 0) 
        cout << "No existe" << endl;
    else  {  
        cout << s.substr(suffarray[ans.second],ans.first).size() << endl;
    }
    return 0;
}
