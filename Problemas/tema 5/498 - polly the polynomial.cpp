#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <string>

using namespace std;

int main()  {
    string caso;
    istringstream aux;
    while(getline(cin,caso))  {
        aux.clear();
        aux.str(caso);
        vector<int> coef,x;
        int n;
        while(aux>>n)
            coef.push_back(n);
        getline(cin,caso);
        aux.clear();
        aux.str(caso);
        while(aux>>n)
            x.push_back(n);
        for (int i=0; i<x.size(); i++)  {
            if(i != 0)
                printf(" ");
            long long r=coef[0];
            for(int j=1; j<coef.size(); j++)   {
                r=r*x[i] + coef[j];
            }
            printf("%lld",r);
        }
        printf("\n");
    }
    return 0;
}
