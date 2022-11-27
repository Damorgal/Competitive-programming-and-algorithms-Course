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

// GCD con el algoritmo de euclides
long long gcd(long long x, long long y) {
    return x ? gcd(y%x, x) : y;
}

class InfiniteSoup  {
    public:
        vector<int> countRays(vector<string> s, vector<string> names, int k)    {
            // Lo haremos con programacion dinamica donde se contendra el numero de palabras
            int dp[100][100];
            int K = (int)s[0].size();
            int N = (int)s.size();
            int D = (int)names.size();
            // Posibles intersecciones
            for(int i=0; i<K; i++)
                for(int j=0; j<N; j++)
                    dp[j][i] = 0;
            for(int i=0; i<=k; i++)
                for(int j=0; j<=k; j++)
                    if(i+j)
                        if(gcd(i,j) == 1)
                            dp[j%N][i%K]++;

            // Verificamos si las palabras coinciden
            vector<int> intersects;
            for(int name=0; name<D; name++)    {
                int cont = 0;
                string aux_name = names[name];
                int aux_tam = (int)aux_name.size();
                int last[60];
                last[0] = 0;

                // Matcheo a primera instancia
                for(int i=0; i<aux_tam; i++)
                    for(int j=0; j<i; j++)  {
                        // Comparamos posible substring
                        string aux_s = aux_name.substr(0,j);
                        string aux_p = aux_name.substr(i-j,j);
                        vector<int> possibleMatches = rabinKarpMatch(aux_s, aux_p);
                        if(!possibleMatches.empty())
                            if(compare(aux_s, aux_p))
                                last[i] = j;
                    }
                // Encontramos posible solucion
                cout << aux_name.c_str() << ": ";
                for(int i=0; i<aux_tam; i++)
                    cout << last[i] << " ";
                cout << endl;
                // Actualizamos dp
                for(int i=0; i<K; i++)
                    for(int j=0; i<N; i++)
                        if(dp[j][i])    {
                            int ind, aux, posi, posj;
                            ind = aux = posi = posj = 0;
                            while(1)    {
                                while(ind && (s[posj][posi] != aux_name[ind]))
                                    ind = last[ind];
                                if(s[posj][posi] == aux_name[ind])
                                    ind++;
                                if(ind == aux_tam)  {
                                    cont += dp[j][i];
                                    break;
                                }
                                posi += i;
                                posi %= K;
                                posj += j;
                                posj %= N;
                                // Si es el inicio
                                if(aux==0 & posi==0 & posj==0)
                                    aux = 1;
                                else if(aux)    {
                                    aux++;
                                    if(aux == aux_tam+5)
                                        break;
                                }
                            }
                }
                intersects.push_back(cont);
            }
            return intersects;
        }
  };
