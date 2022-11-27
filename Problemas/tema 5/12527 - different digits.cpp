#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <algorithm>

using namespace std;

int cont;

int checa(int n, int b)    {
    int u,d,c,m,con;
    for(con=0; n!=0; n /= 10, con++)  {
        if(con==0)
            u = n%10;
        else if(con==1)
            d = n%10;
        else if(con==2)
            c = n%10;
        else if(con==3)
            m = n%10;
    }
    if(con==1)  {
        cont ++;
        return 0;
    }
    if(con==2)  {
        if(d!=u)
            cont++;
        return 0;
    }
    if(con==3)  {
        if(d!=u && c!=u && c!=d)    {
            cont++;
            return 0;
        }
        if(c==d)    {
            int aux=u+1;
            return 10-aux;
        }
        return 0;
    }
    if(con==4)  {
        if(d!=u && c!=u && c!=d && m!=c && m!=d && m!=u)    {
            cont++;
            return 0;
        }
        if(c==m)    {
            int aux=10*d+u+1;
            return 100-aux;
        }
        return 0;
    }
}

int main()  {
    int vec[5001];
    int a,b;
    while(cin>>a>>b)    {
        cont=0;
        for(int i=a; i<=b; i++)  {
            i += checa(i,b);
        }
        cout<<cont<<endl;
    }
    return 0;
}