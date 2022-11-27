#include <iostream>

using namespace std;

int values[1000][1000];

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

vector<int> tripleMatch(const string& s1, const string& s2, const string& s3)   {
    const int p = 31;
    const int m = 1000000007;
    
    // Precompute modular powers
    vector<long long> pi(s.size());
    pi[0] = 1;
    for (int i = 1; i < s.size(); i++)
        pi[i] = (pi[i-1] * p) % m;
    
    // Precompute the hash value for all the prefixes of s1, s2 and s3
    vector<long long> hashed_prefixes_s1(s1.size() + 1, 0);
    vector<long long> hashed_prefixes_s2(s2.size() + 1, 0);
    vector<long long> hashed_prefixes_s3(s3.size() + 1, 0);
    for (int i = 0; i < s.size(); i++)  {
        hashed_prefixes_s1[i+1] = (hashed_prefixes_s1[i] + (s1[i] - 'a' + 1) * pi[i]) % m;
        hashed_prefixes_s2[i+1] = (hashed_prefixes_s2[i] + (s2[i] - 'a' + 1) * pi[i]) % m;
        hashed_prefixes_s3[i+1] = (hashed_prefixes_s3[i] + (s3[i] - 'a' + 1) * pi[i]) % m;
    }
    
    // Compare sub-string hashes
    vector<int> found;
    for (int i = 0; i + pattern.size() - 1 < s.size(); i++) {
        long long hashed = (hashed_prefixes[i+pattern.size()] + m - hashed_prefixes[i]) % m;
        if (hashed == hashed_pattern * pi[i] % m)
            found.push_back(i);
    }
    return found;
}

int main() {
    string s1,s2;
    values[0][0]=0;
    for(int i=0; i<102; i++) {
        values[i][0] = 0;
        values[0][i] = 0;
    }
    getline(cin,s1);
    getline(cin,s2);
    for(int i=0; i<s1.size(); i++)
        for(int j=0; j<s2.size(); j++) {
            int m = values[i][j+1];
            int n = values[i+1][j];
            values[i+1][j+1] = max(m,n);
            if(s1[i] == s2[j])
                values[i+1][j+1] = max(values[i+1][j+1], values[i][j]+1);
        }
    cout << (s1.size()+s2.size()) - 2*values[s1.size()][s2.size()] << endl;
    return 0;
}
