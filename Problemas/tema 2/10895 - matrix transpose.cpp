#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <cmath>
#include <vector>

using namespace std;

vector< pair<int,int> > vec[10001];

int main()  {
    ios::sync_with_stdio(false);
    int m,n;
    while(cin>>m>>n)    {
        for(int i=0; i<=10000; i++)
            vec[i].clear();

        int fila=0;
        for(int i=1; i<=m; i++)   {
            int k;
            cin >> k;
            int a[k+1];
            for(int i=1; i<=k; i++)
                cin>>a[i];
            fila++;
            for(int i=1; i<=k; i++) {
                int aux;
                cin>>aux;
                vec[a[i]].push_back(make_pair(fila,aux));
            }
        }
        cout<<n<<" "<<m<<endl;
        for(int i=1; i<=n; i++) {
            if(vec[i].size() > 0) {
                cout<<vec[i].size()<<" ";
                for(int j=0; j<vec[i].size(); j++)  {
                    if(j == (vec[i].size()-1))
                        cout<<vec[i][j].first<<endl;
                    else
                        cout<<vec[i][j].first<<" ";
                }
                for(int j=0; j<vec[i].size(); j++)    {
                    if(j == (vec[i].size()-1))
                        cout<<vec[i][j].second<<endl;
                    else
                        cout<<vec[i][j].second<<" ";
                }
            }
            else
                cout<<0<<endl<<endl;
        }
    }
    return 0;
}
