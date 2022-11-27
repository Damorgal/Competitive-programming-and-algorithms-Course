#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <cmath>

#define inf 1000000000

using namespace std;

int n,m,vessels[1100];
bool llena(int cap) {
    int act=cap;
    int container=1;
    for(int i=0; i<n; i++)  {
        if(vessels[i] > cap)
            return false;
        if(vessels[i] > act)    {
            if (container == m)
                return false;
            container++;
            act = cap;
        }
        act -= vessels[i];
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    while(scanf("%d %d",&n,&m) == 2)    {
        for(int i=0; i<n; i++)
            scanf("%d",&vessels[i]);
        int l = 1;
        int h = inf;
        int ans = 0;
        while(l<=h) {
            int mid = (h+l)/2;
            if(llena(mid))  {
                ans = mid;
                h = mid-1;
            }
            else
                l = mid+1;
        }
        printf("%d\n",ans);
    }
    return 0;
}
