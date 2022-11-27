#include <iostream>

using namespace std;

int repetidos(int v[], int n)   {
    for(int tam=2; tam<=n+1; tam+=2)   
        for(int i=0; i<n-tam+2; i++)    
            if(v[i] == v[i+tam-1])
                return v[i];
    for(int tam=3; tam<=n+1; tam+=2)   
        for(int i=0; i<n-tam+2; i++)    
            if(v[i] == v[i+tam-1])
                return v[i];
    return 0;
}

int main()  {
    int vec[1000000];
    int n;
    cin >> n;
    for(int i=0; i<=n; i++)
        cin >> vec[i];
    printf("%d\n", repetidos(vec,n));
    return 0;
}
