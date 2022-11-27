#include <iostream>
#include <stdio.h>
#include <vector>
#include <queue>
#include <cstring>
#include <stdlib.h>

using namespace std;

int r,c;
int cx[4];//checkpoint[*x-y*][*1-2-3*];
int cy[4];
bool vs[10][10];
int cp[4];
int x[8] = { 0, 0, 1, -1, -1, 1, -1, 1};
int y[8] = { 1, -1, 0, 0, -1, 1, 1, -1};
int cont;
queue< pair<int, int> > q;

void dfs(const int &tfi,const int &tse, const int &w);
bool verifica(const int &px, const int &py, const int &pos);

int main()  {
    int caso = 1;

    // Leemos las variables hasta que éstas sean 0
    //cin >> r >> c;
    scanf("%d %d",&r,&c);
    while(r != 0 && c != 0) {
        for(int i = 0; i < 3; i++)  {
            int aux1, aux2;
            //cin >> aux2 >> aux1;
            scanf("%d %d",&aux2,&aux1);
            cx[i] = aux1;
            cy[i] = (r-1) - aux2;
        }
        memset(vs, 0, sizeof vs);
        cp[0] = (r*c)/4;
        cp[1] = (r*c)/2;
        cp[2] = ((r * c) * 3.0)/4;
        cp[3] = r*c;
        cx[3] = 1;
        cy[3] = r-1;
        cont = 0;

        dfs(r-1, 0, 1);

        //cout << "Case " << caso++ << ": " << cont <<endl;
        printf("Case %d: %d\n",caso, cont);
        caso++;
        //cin >> r >> c;
        scanf("%d %d",&r,&c);
    }

    return 0;
}

bool verifica(const int &px, const int &py, const int &pos)    {
    for(int i = 0; i < 4; i++)  {
        if(pos == cp[i])    {
            if(cx[i] != px || cy[i] != py)
                return false;
        }
        else    {
            if(cx[i] == px && cy[i] == py)
                return false;
        }
        if(pos < cp[i]) {
            int manh = abs(cx[i] - px) + abs(cy[i] - py);
            if( pos + manh > cp[i] )
                return false;
        }
    }
    bool vis[10][10];
    pair<int, int> t;
    memset(vis, 0, sizeof vis);

    int cont1 = 0, cont2 = 0;
    vis[py][px] = true;
    for(int i = 0; i < r; i++)  {
        for(int k = 0; k < c; k++)  {
            vis[i][k] = vs[i][k];
            if(!vis[i][k])  {
                cont1++;
                if(q.empty())   {
                    vis[i][k] = true;
                    cont2++;
                    q.push(pair<int, int> (i,k));
                }
            }

        }
    }
    while(!q.empty())   {
        t = q.front();
        q.pop();

        for(int m = 0; m < 4; m++)  {
            int asd = t.first + y[m];
            int bsd = t.second + x[m];
            if(asd < 0 || bsd < 0 || asd >= r || bsd >= c)
                continue;
            if(vis[asd][bsd])
                continue;
            vis[asd][bsd] = true;
            cont2++;
            q.push(pair <int, int> (asd,bsd));
        }
    }
    return cont1 == cont2;
}

void dfs(const int &tfi, const int &tse, const int &w)   {
    if(!verifica(tse, tfi, w))
        return;
    vs[tfi][tse] = true;

    if(w==cp[3])    {
        cont++;
        vs[tfi][tse] = false;
        return;
    }
    int as,bs;
    int asw, bsw;
    int conttemp = 0;
    int itemp = 0;
    for(int m = 0; m < 4; m++)  {
        as = tfi + y[m];
        bs = tse + x[m];
        int veci = 0;
        if(as < 0 || bs < 0 || as >= r || bs >= c)
            continue;
        if(vs[as][bs])
            continue;
        for(int o = 0; o < 4; o++)  {
            asw = as + y[m];
            bsw = bs + x[m];
            int veci = 0;
            if(asw < 0 || bsw < 0 || asw >= r || bsw >= c)
                continue;
            if(!vs[asw][bsw])
                veci++;
        }
        if(veci == 1)   {
            conttemp++;

            itemp = m;
        }
    }

    if(conttemp > 1)    {
        vs[tfi][tse] = false;
        return;
    }
    if(conttemp == 1)   {
        as = tfi + y[itemp];
        bs = tse + x[itemp];
        dfs(as,bs,w+1);
        vs[tfi][tse] = false;
        return;
    }
    for(int m = 0; m < 4; m++)  {
        as = tfi + y[m];
        bs = tse + x[m];
        if(as < 0 || bs < 0 || as >= r || bs >= c)
            continue;
        if(!vs[as][bs])
            dfs(as,bs, w+1);
    }
    vs[tfi][tse] = false;
}
