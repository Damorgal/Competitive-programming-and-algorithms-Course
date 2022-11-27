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

int tripleMatch(string& s1, string& s2, string& s3)   {
    // Intercambiamos para tener orden en los tamaños
    if((int)s1.size() < (int)s2.size())
        swp(s1, s2);
    if((int)s1.size() < (int)s3.size())
            swp(s1, s3);
    if((int)s2.size() < (int)s3.size())
        swp(s2, s3);
    // Vemos si una cadena esta contenida en otra
    vector<int> possibleMatches = rabinKarpMatch(s1, s2);
    int maxMatchI_s1s2 = 0, maxMatchD_s1s2 = 0;
    if(!compare(possibleMatches, s1, s2))   {
        // Matcheo parciales
        string aux_s, aux_p;
        for(int i=0; i<(int)s2.size()-1; i++)    {
            // Matcheo por la izquierda
            aux_s = s1.substr(0,i+1);
            aux_p = s2.substr((int)s2.size()-1-i);
            vector <int> pMatch = rabinKarpMatch(aux_s, aux_p);
            if(!pMatch.empty())
                if(compare(aux_s, aux_p))
                    if(maxMatchI_s1s2 < (int)aux_p.size())
                        maxMatchI_s1s2 = (int)aux_p.size();
            // Matcheo por la derecha
            aux_s = s1.substr((int)s1.size()-1-i);
            aux_p = s2.substr(0,i+1);
            pMatch = rabinKarpMatch(aux_s, aux_p);
            if(!pMatch.empty())
                if(compare(aux_s, aux_p))
                    if(maxMatchD_s1s2 < (int)aux_p.size())
                        maxMatchD_s1s2 = (int)aux_p.size();
        }
    }
    else
        maxMatchI_s1s2 = maxMatchD_s1s2 = (int)s2.size();

    // Lo mismo pero ahora para s1 y s3
    // Vemos si una cadena esta contenida en otra
    possibleMatches = rabinKarpMatch(s1, s3);
    int maxMatchI_s1s3 = 0, maxMatchD_s1s3 = 0;
    if(!compare(possibleMatches, s1, s3))   {
        // Matcheo parciales
        string aux_s, aux_p;
        for(int i=0; i<(int)s3.size()-1; i++)    {
            // Matcheo por la izquierda
            aux_s = s1.substr(0,i+1);
            aux_p = s3.substr((int)s3.size()-1-i);
            vector <int> pMatch = rabinKarpMatch(aux_s, aux_p);
            if(!pMatch.empty())
                if(compare(aux_s, aux_p))
                    if(maxMatchI_s1s3 < (int)aux_p.size())
                        maxMatchI_s1s3 = (int)aux_p.size();
            // Matcheo por la derecha
            aux_s = s1.substr((int)s1.size()-1-i);
            aux_p = s3.substr(0,i+1);
            pMatch = rabinKarpMatch(aux_s, aux_p);
            if(!pMatch.empty())
                if(compare(aux_s, aux_p))
                    if(maxMatchD_s1s3 < (int)aux_p.size())
                        maxMatchD_s1s3 = (int)aux_p.size();
        }
    }
    else
        maxMatchI_s1s3 = maxMatchD_s1s3 = (int)s3.size();

    // Lo mismo pero ahora para s2 y s3
    // Vemos si una cadena esta contenida en otra
    possibleMatches = rabinKarpMatch(s2, s3);
    int maxMatchI_s2s3 = 0, maxMatchD_s2s3 = 0;
    if(!compare(possibleMatches, s2, s3))   {
        // Matcheo parciales
        string aux_s, aux_p;
        for(int i=0; i<(int)s3.size()-1; i++)    {
            // Matcheo por la izquierda
            aux_s = s2.substr(0,i+1);
            aux_p = s3.substr((int)s3.size()-1-i);
            vector <int> pMatch = rabinKarpMatch(aux_s, aux_p);
            if(!pMatch.empty())
                if(compare(aux_s, aux_p))
                    if(maxMatchI_s2s3 < (int)aux_p.size())
                        maxMatchI_s2s3 = (int)aux_p.size();
            // Matcheo por la derecha
            aux_s = s2.substr((int)s2.size()-1-i);
            aux_p = s3.substr(0,i+1);
            pMatch = rabinKarpMatch(aux_s, aux_p);
            if(!pMatch.empty())
                if(compare(aux_s, aux_p))
                    if(maxMatchD_s2s3 < (int)aux_p.size())
                        maxMatchD_s2s3 = (int)aux_p.size();
        }
    }
    else
        maxMatchI_s2s3 = maxMatchD_s2s3 = (int)s3.size();

    // Maximo matcheo posible
    int maxMatch = (int)s1.size();
    if(maxMatchD_s1s2 == (int)s2.size()) {
        if(maxMatchD_s1s3 == (int)s3.size())
            return maxMatch;
        else    {
            if(maxMatchD_s1s3 < maxMatchI_s1s3)
                return maxMatch + (int)s3.size() - maxMatchI_s1s3;
            else
                return maxMatch + (int)s3.size() - maxMatchD_s1s3;
        }
    }
    else    {
        // Minima longitud (maximo matcheo) posible
        vector<int> possibleMin;
        possibleMin.push_back(maxMatch + (int)s2.size()-maxMatchD_s1s2 + (int)s3.size()-maxMatchD_s2s3);
        possibleMin.push_back(maxMatch + (int)s2.size()-maxMatchD_s1s2 + (int)s3.size()-maxMatchI_s1s3);
        possibleMin.push_back(maxMatch + (int)s2.size()-maxMatchI_s1s2 + (int)s3.size()-maxMatchI_s2s3);
        possibleMin.push_back(maxMatch + (int)s2.size()-maxMatchI_s1s2 + (int)s3.size()-maxMatchD_s1s3);
        possibleMin.push_back(maxMatch + (int)s3.size()-maxMatchI_s1s3 + (int)s2.size()-maxMatchD_s2s3);
        possibleMin.push_back(maxMatch + (int)s3.size()-maxMatchD_s1s3 + (int)s2.size()-maxMatchI_s2s3);
        // Minimo
        int mini = possibleMin[0];
        for(int i=1; i<(int)possibleMin.size(); i++)
            if(possibleMin[i] < mini)
                mini = possibleMin[i];
        return mini;
    }
}

int main() {
    string s1,s2,s3;
    getline(cin,s1);
    getline(cin,s2);
    getline(cin,s3);
    cout << tripleMatch(s1,s2,s3) << endl;
    return 0;
}
