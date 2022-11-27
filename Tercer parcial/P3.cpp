#include <iostream>
#include <vector>
#include <string.h>
#include <cmath>

using namespace std;

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

void contruye_z(string &s)  {
    int k,l;
    k = l =1;
    for(int i=1; i<s.size(); i++)   {
        if(i<=l)    {
            
        }
        else    {
            string p = s.substr(k,l-k);
            kmpPreprocess(p);
            int nc = kmpMatch(s.substr(0,l-k),p);
            if(nc)
                z[i] = l-k;
            else
                z[i] = 0;
        }
    }
}


int main() {
    ios::sync_with_stdio(false);
    int N;
    cin >> N;
    cout << solve(N) << endl;
    return 0;
}
