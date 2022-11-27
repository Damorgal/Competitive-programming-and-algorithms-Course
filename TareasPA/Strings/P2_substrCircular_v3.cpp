#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

inline int gcd(int a, int b)    {
    if (a == 0)
        return b;
    return gcd(b%a, a);
}

inline long long pow_mod(long long a, unsigned long long b, unsigned long long m)  {
    if(b == 0)
        return 1;
    long long p = pow_mod(a,b/2,m) % m;
    p = (p*p) % m;
    return (b%2 == 0) ? p : (a*p)%m;
}

int rabinKarpMatch(int K, int D, string& s, string* pattern) {
    const int p = 31;
    const int m = 1000000007;

    // Precompute modular powers
    vector<long long> pi(s.size());
    pi[0] = 1;
    for(int i=1; i<s.size(); i++)
        pi[i] = (pi[i-1]*p) % m;

    // Precompute the hash value for all the prefixes of s
    // Does not depend on the pattern
    vector<long long> hashed_prefixes(s.size()+1, 0);
    for (int i=0; i<s.size(); i++)
        hashed_prefixes[i+1] = (hashed_prefixes[i] + (s[i] - 'a'+1)*pi[i]) % m;

    // Compute the hash value for pattern
    set <long long> hashed_pattern;
    long long aux;
    for(int j=0; j<D; j++)  {
        aux = 0;
        for (int i=0; i<pattern[j].size(); i++)
            aux = (aux+(pattern[j][i]-'a'+1) * pi[i]) % m;
        hashed_pattern.insert(aux);
    }
    vector<set <long long> > v;
    v.assign(K, set<long long>());

    // Compare sub-string hashes
    for (int i=0; i+pattern[0].size()-1<s.size(); i++)  {
        long long hashed = (hashed_prefixes[i+pattern[0].size()]+ m - hashed_prefixes[i]) % m;
        long long h = gcd(pi[i],m);
        if(h != 1)
            h = -1;
        else
            h = pow_mod(pi[i],m-2,m);
        h = hashed*h % m;
        set<long long>::iterator it = hashed_pattern.find(h);
        if(it!=hashed_pattern.end())    {
            v[i%K].insert(h);
        }
    }
    int aux_max = 0;
    for(int i=0; i<K; i++)
        aux_max = max(aux_max, (int)v[i].size());

    return aux_max;
}

bool theory(int N, int K, int D, string& s, string* names)   {
    if(rabinKarpMatch(K,D,s,names) == N)
        return true;
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    int D,N,K;
    string s,aux;
    cin >> D;
    cin >> N;
    cin >> K;
    getline(cin,s);
    getline(cin,s);
    string names[D];
    for(int i=0; i<D; i++)
        getline(cin,names[i]);
    if(theory(N,K,D,s.append(s),names))
        cout << "true" << endl;
    else
        cout << "false" << endl;
    return 0;
}
