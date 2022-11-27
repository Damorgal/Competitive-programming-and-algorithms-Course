#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <queue>
#include <string>

using namespace std;

int main(int argv, const char * argc[]) {
    ios::sync_with_stdio(false);
    string s, ss("#");
    int n, p, q;
    priority_queue<pair<int, pair<int, int> >,
    vector<pair<int, pair<int, int> > >,
    greater<pair<int, pair<int, int> > > > P;

    cin >> s;
    while (s != ss) {
        scanf("%d %d",&q,&p);
        P.push(pair<int, pair<int, int> >(p, pair<int, int>(q, p)));
        cin>>s;
    }
    scanf("%d",&n);
    while(n--)  {
        pair<int, pair<int, int> > pr = P.top();
        P.pop();
        printf("%d\n",pr.second.first);
        pr.first += pr.second.second;
        P.push(pr);
    }
    return 0;
}
