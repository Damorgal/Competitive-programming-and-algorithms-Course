#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <cmath>
#include <algorithm>

using namespace std;

int n,m;
int *vec;

bool verifica(int medio) {
    int vis=1;
    int rango=vec[0] + medio;
    for(int i=0; i<m; i++)  {
        if(vec[i]>rango)    {
            rango=vec[i] + medio;
            vis++;
        }
    }
    return(vis<=n);
}

int main() {
    int t;
    cin>>t;
    while(t--)  {
        cin>>n>>m;
        vec=(int*)malloc(m*sizeof(int));
        for(int i=0; i<m; i++)
            cin>>vec[i];
        if(n>=m)   {
            printf("0.0\n");
            continue;
        }
        sort(vec, vec+m);
        int l=0;
        int h=1000000;
        while(h-l > 1) {
            int medio=(l+h)/2;
            if(verifica(2*medio))
                h=medio;
            else
                l=medio;
        }
        l *= 10;
        h *= 10;
        for(int i=0; i<m; i++)
            vec[i] *= 10;
        while(h-l> 1) {
            int medio=(l+h)/2;
            if(verifica(2*medio))
                h=medio;
            else
                l=medio;
        }
        printf("%d.%d\n",h/10,h%10);
        free(vec);
    }
    return 0;
}
