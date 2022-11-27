#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> rabinKarpMatch(const string& s, const string& pattern) {
    const int p = 31;
    const int m = 1000000007;

    // Precompute modular powers
    vector<long long> pi(s.size());
    pi[0] = 1;
    for (int i = 1; i < s.size(); i++)
        pi[i] = (pi[i-1] * p) % m;

    // Precompute the hash value for all the prefixes of s
    // Does not depend on the pattern
    vector<long long> hashed_prefixes(s.size() + 1, 0);
    for (int i = 0; i < s.size(); i++)
        hashed_prefixes[i+1] = (hashed_prefixes[i] + (s[i] - 'a' + 1) * pi[i]) % m;

    // Compute the hash value for pattern
    long long hashed_pattern = 0;
    for (int i = 0; i < pattern.size(); i++)
        hashed_pattern = (hashed_pattern + (pattern[i] - 'a' + 1) * pi[i]) % m;

    // Compare sub-string hashes
    vector<int> found;
    for (int i = 0; i + pattern.size() - 1 < s.size(); i++) {
        long long hashed = (hashed_prefixes[i+pattern.size()] + m - hashed_prefixes[i]) % m;
        if (hashed == hashed_pattern * pi[i] % m)
            found.push_back(i);
    }
    return found;
}

bool compare(const vector<int>& v, const string& s, const string& p)    {
    for(int i=0; i<(int)v.size(); i++)   {
        int cont = 0;
        for(int k=v[i]; k<v[i]+(int)p.size(); k++)
            if(s[k] == p[k-v[i]])
                cont++;
            else
                break;
        if(cont == (int)p.size())
            return true;
        else
            cont = 0;
    }
    return false;
}

bool compare(const string& s, const string& p)    {
    int cont = 0;
    for(int k=0; k<(int)p.size(); k++)
        if(s[k] == p[k])
            cont++;
        else
            break;
    if(cont == (int)p.size())
        return true;
    return false;
}

inline void swp(string& s1, string& s2)  {
    string aux = s1;
    s1 = s2;
    s2 = aux;
}

bool theory(int N, int K, string& s, vector<string>& names)   {
    vector<int> possibleMatches;
    int lastPos;
    // Buscamos los posibles nombres
    for(int i=0; i<(int)names.size(); i++)  {
        possibleMatches = rabinKarpMatch(s, names[i]);
        if(!possibleMatches.empty())
            for(int j=0; j<(int)possibleMatches.size(); j++)    {
                if(compare(s.substr(possibleMatches[j],K), names[i])) {
                    // Si hubo match, quitamos el nombre y la parte de substr
                    lastPos = i;
                    names[i] = names.back();
                    names.pop_back();
                    if(i+K < (int)s.size())
                        s = (s.substr(0,i)).append(s.substr(i+K));
                    else
                        s = (s.substr(0,i));
                }
            }
    }
    // Lo que queda solo debe ser un string de tamaño K
    if((int)s.size() != K)
        return false;
    // Buscamos el nuevo nombre que falta debe empezar lastPos
    lastPos %= (int)s.size();
    s = (s.substr(lastPos)).append(s.substr(0,lastPos));
    for(int i=0; i<(int)names.size(); i++)  {
        possibleMatches = rabinKarpMatch(s, names[i]);
        if(!possibleMatches.empty())
            if(compare(s,names[i]))
                return true;
    }
    // No hubo ningun match
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    int D,N,K;
    string s,aux;
    vector<string> names;
    cin >> D;
    cin >> N;
    cin >> K;
    getline(cin,s);
    getline(cin,s);
    while(D--)  {
        getline(cin,aux);
        names.push_back(aux);
    }
    if(theory(N,K,s,names))
        cout << "true" << endl;
    else
        cout << "false" << endl;
    return 0;
}
