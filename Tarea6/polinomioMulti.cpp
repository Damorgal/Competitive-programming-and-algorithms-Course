#include <iostream>
#include <stdlib.h>
#include <vector>
#include <math.h>

using namespace std;

long long int factorial(int n)  {
    long long int ans=n;
    while(--n)
        ans *= n;
    return ans;
}

long long int coefpolinomio(int vec[], int n, int k)   {
    long long int ans=1;
    for(int i=n; i>vec[0]; i--)
        ans *= i;
    for(int i=1; i<k; i++)
        ans /= factorial(vec[i]);
    return ans;
}

int main()  {
    int n=8, k=3, i_s[] = {2,3,3};
    long long int ans;
    ans = coefpolinomio(i_s,n,k);
    cout<< "El coeficiente es: "<< ans <<endl;
    return 0;
}
