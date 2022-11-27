#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <cmath>
#include <set>

using namespace std;

int main()  {
    ios::sync_with_stdio(false);
    int n;
    while(cin>>n && n)  {
        multiset<int> bills;
        long long suma=0;
        int m,b;
        for(int i=0; i<n; i++)  {
            cin>>m;
            for(int j=0; j<m; j++) {
                cin>>b;
                bills.insert(b);
            }
            suma += *(--bills.end()) - *bills.begin();
            bills.erase(bills.begin());
            bills.erase(bills.find(*bills.rbegin()));
        }
        cout<<suma<<endl;
    }
    return 0;
}
