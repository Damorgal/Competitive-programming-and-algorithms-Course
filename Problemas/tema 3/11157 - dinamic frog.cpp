#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> vec;

int main() {
    int t,n,d;
    int caso=1;
    cin>>t;
    while(t--)  {
        cin>>n>>d;
        char a;
        int b;
        vec.clear();
        vec.push_back(0);
        vec.push_back(d);
        for(int i=0; i<n; i++)   {
            cin>>a;
            cin.ignore();
            cin>>b;
            vec.push_back(b);
            if(a=='B')
                vec.push_back(b);
        }
        sort(vec.begin(),vec.end());
        int maximo=0;
        for(int i=3; i<vec.size(); i+=2)
            maximo = max(maximo, vec[i]-vec[i-2]);
        for(int i=2; i<vec.size(); i+=2)
            maximo = max(maximo, vec[i]-vec[i-2]);
        printf("Case %d: %d\n",caso++,maximo);
    }
    return 0;
}
