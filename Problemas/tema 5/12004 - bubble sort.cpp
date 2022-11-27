#include <iostream>
#include <stdio.h>
#include <cstdlib>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    int K,n;
    cin>>K;
    for(int caso=1; caso<=K; caso++)  {
        cin>>n;
        long long ans = (long long)n*(n-1)/2;
        printf("Case %d: ",caso);
        if(ans%2)
            printf("%lld/2\n",ans);
        else
            printf("%lld\n",ans/2);
    }
    return 0;
}
