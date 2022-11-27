#include <iostream>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <algorithm>

using namespace std;
int resets[100000];

void kmpPreprocess(const string &p) {
    int i=0, j=-1;
    resets[0] = -1;
    while(i < p.size()) { 
        while(j>=0 && p[i]!=p[j]) 
            j = resets[j];
        i++;
        j++;
        resets[i] = j;
    }
}

// Cuenta el numero de ocurrencias del patron en s
int kmpMatch(const string &s, const string &pattern) {
    int i=0, j=0, nc=0;
    while(i < s.size()) {
        while(j>=0 && s[i]!=pattern[j]) 
            j = resets[j];
        i++; 
        j++;
        if(j == pattern.size()) {
            nc++;
            j = resets[j];
        }
    }
    return nc;
}

/*
// Variante del kmpMatch que regresa el matcheo parcial más grande
int kmpMatch(const string &s, const string &pattern)    {
    int i=0, j=0, jmax=-1;
    while(i < s.size()) {
        // Mismatch
        if(j>=0 && s[i]!=pattern[j])    {
            while(j>=0 && s[i]!=pattern[j]) 
                j = resets[j];
        } 
        else if(j > jmax) 
            jmax = j;
        i++; 
        j++;
    }
    return jmax;
}
*/
int main()  {
    ios::sync_with_stdio(false);
    string p,s;
    getline(cin,p);
    getline(cin,s);
    int np = p.size();
    bool ind = 0;
    int count = 0;
    for(int i=0; i<26; i++) {
        //Hacemos los shifts
        if(i != 0)  { 
            for(int j=0; j<np; j++) {
                p[j]++;
                if(p[j] > 90)  
                    p[j] = 65;
            }
        }
        kmpPreprocess(p);
        int nc = kmpMatch(s,p);
        if(nc == 1)
            count++;
    }
    cout << count << endl;
    return 0;
}
