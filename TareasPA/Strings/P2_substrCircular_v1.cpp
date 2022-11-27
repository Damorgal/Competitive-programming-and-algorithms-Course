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
    // Vemos el primer matcheo posible
    vector<int> possibleMatches;
    int pos;
    while(1)    {
        // Buscamos desde atras para simular una pila
        possibleMatches = rabinKarpMatch(s, names.back());
        pos = -1;
        // Vemos si hubo un matcheo interno
        for(int i=0; i<(int)possibleMatches.size(); i++)    {
            if(compare(s.substr(possibleMatches[i],K), names.back())) {
                pos = possibleMatches[i];
                break;
            }
        }
        // Si sí hubo salimos
        if(pos != -1)
            break;
        // Si no hubo buscamos posibles matcheos en los extremos
        else    {
            // Matcheo parciales
            string aux_s, aux_p;
            for(int i=0; i<(int)(names.back()).size()-1; i++)    {
                // Matcheo por la izquierda
                aux_s = s.substr(0,i+1);
                aux_p = (names.back()).substr((int)(names.back()).size()-1-i);
                vector <int> pMatch = rabinKarpMatch(aux_s, aux_p);
                if(!pMatch.empty())
                    if(compare(aux_s, aux_p))   {
                        // Matcheo por la derecha
                        aux_s = s.substr((int)s.size()-1-i);
                        aux_p = (names.back()).substr(0,i+1);
                        pMatch = rabinKarpMatch(aux_s, aux_p);
                        if(!pMatch.empty())
                            if(compare(aux_s, aux_p))   {
                                pos = (int)s.size()-1-i;
                                break;
                            }
                    }
            }
            // Si sí hubo salimos
            if(pos != -1)
                break;
        }
        if(names.empty())
            return false;
        names.pop_back();
    }

    // Verificamos que este de manera circular
    while(N--)  {
        names.pop_back();
        pos += K;
        pos %= (int)s.size();
        string p;
        if(pos+K > (int)s.size()-1)
                p = (s.substr(pos)).append(s.substr(0,(pos+K)%(int)s.size()));
            else
                p = s.substr(pos, K);
        for(int i=0; i<(int)names.size(); i++)  {
            possibleMatches = rabinKarpMatch(names[i], p);
            if(!possibleMatches.empty())
                if(compare(names[i], p))    {
                        names[i] = names.back();
                        break;
                }
            if((int)names.size()-1 == i)
                return false;
        }
    }
    return true;
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
