#include <iostream>

using namespace std;

int values[1000][1000];

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
