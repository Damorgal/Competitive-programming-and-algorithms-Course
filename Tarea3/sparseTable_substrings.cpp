#include <stdlib.h>
#include <cmath>
#include <iostream>
#include <vector>
#include <utility>

using namespace std;

vector<vector<pair<int,int>>> createSparseTable(int *v, int N)    {
    int difMax=N, logN=0;
    // logN = ceil(log2(N))
    while(difMax >>= 1) logN++;
    if(1<<logN < N) logN++;
    
    /*
    // Memoria para la sparse table
    int **ST = (int**)malloc(N*sizeof(int*));
    if(ST == NULL) return NULL;
    ST[0] = (int*)malloc(N*logN*sizeof(int));
    if(ST[0] == NULL) return NULL;
    for(int t=1; t<N; t++)
        ST[t] = ST[t-1] + logN;
    */
    vector<vector<pair<int,int>>> ST;
    
    // Llenado de tabla 
    for(int j=0; j<logN; j++)   {
        for(int i=0; i<N; i++)  {
            // Dif. max de long. 1
            if(j==0)    {
                vector<pair<int,int>> aux;
                aux.push_back(make_pair(v[i],v[i]));
                ST.push_back(aux);
            }
            // Dif. max de long. 2
            else if(j==1)    {
                if(i+1 < N)   {
                    int mi = v[i], ma = v[i+1];
                    if(mi>ma) 
                        swap(mi,ma);
                    ST[i].push_back(make_pair(mi,ma));
                }
            }
            // Dif. max. de long mayor
            else    {
                //if(i+pow(2,j)<=N)   {
                if(i+(1<<j)<=N)   {
                    int mi = ST[i][j-1].first, ma = ST[i][j-1].second;
                    //difMax = ST[i][j-1];
                    //int aux = i+pow(2,j-1);
                    int aux = i+(1<<(j-1));
                    if(mi>ST[aux][j-1].first)
                        mi=ST[aux][j-1].first;
                    if(ma<ST[aux][j-1].second)
                        ma=ST[aux][j-1].second;
                    ST[i].push_back(make_pair(mi,ma));
                }
                else
                    //ST[i][j] = -1;
                    break;
            }
        }
    }
    return ST;
}
/*
int main()  {
    int N, k, *vec,ans;
    scanf("%d %d",&N,&k);
    ans = 0;
    // Memoria para el arreglo
    vec = (int*)malloc(N*sizeof(int));
    // Leemos el arreglo
    for(int t=0; t<N; scanf("%d", &vec[t++]));
    // Creamos sparse table de minimos y maximos
    vector<vector<pair<int,int>>> ST = createSparseTable(vec,N);
    
    // Contamos los substrings
    for(int i=0; i<N; i++)  {
        int tam=2,tamMax=0,top=N;
        while(1)    {
            for(; tam<=top; tam = tamMax+((tam-tamMax)<<1))    {
                //cout<<"caso tam="<<tam<<" ini="<<i<<endl;
                if(tam==2 && tam+i<=top)    {
                    // Recordar que 2=2^1 entonces esta en la posicion 1
                    if(ST[i][1].second-ST[i][1].first > k)
                        break;
                }
                // Respuesta O(1)
                else if(tam+i <= top)  {
                    int logtam = 0, dist=tam, inicio=i, mi, ma;
                    while(dist >>= 1) logtam++;
                    mi = ST[inicio][logtam].first; 
                    ma = ST[inicio][logtam].second;
                    inicio = (inicio+tam)-(1<<logtam); 
                    if(mi > ST[inicio][logtam].first)
                        mi = ST[inicio][logtam].first; 
                    if(ma < ST[inicio][logtam].second)
                        ma = ST[inicio][logtam].second;
                    if(ma-mi > k)
                        break;
                }
                else
                    break;
            }
            tamMax += ((tam-tamMax)>>1);
            if(tamMax+i == top)
                break;
            if(tam+i-1 < top) 
                top = tam+i-1;
            
            tam = tamMax+1;
            
        }
        ans += tamMax;
    }
    printf("%d",ans);
    free(vec);
    return 0;
}

*/
int main()  {
    int N, k, *vec,ans;
    scanf("%d %d",&N,&k);
    ans = 0;
    // Memoria para el arreglo
    vec = (int*)malloc(N*sizeof(int));
    // Leemos el arreglo
    for(int t=0; t<N; scanf("%d", &vec[t++]));
    // Creamos sparse table de minimos y maximos
    vector<vector<pair<int,int>>> ST = createSparseTable(vec,N);
    
    // Contamos los substrings
    for(int i=0; i<N; i++)  {
        int tam=2,tamMax=0;
            /*for(; tam<=N; tam = tam<<1)    {
                //cout<<"caso tam="<<tam<<" ini="<<i<<endl;
                if(tam==2 && tam+i<=N)    {
                    // Recordar que 2=2^1 entonces esta en la posicion 1
                    if(ST[i][1].second-ST[i][1].first > k)
                        break;
                }
                // Respuesta O(1)
                else if(tam+i <= N)  {
                    int logtam = 0, dist=tam, inicio=i, mi, ma;
                    while(dist >>= 1) logtam++;
                    mi = ST[inicio][logtam].first; 
                    ma = ST[inicio][logtam].second;
                    inicio = (inicio+tam)-(1<<logtam); 
                    if(mi > ST[inicio][logtam].first)
                        mi = ST[inicio][logtam].first; 
                    if(ma < ST[inicio][logtam].second)
                        ma = ST[inicio][logtam].second;
                    if(ma-mi > k)
                        break;
                }
                else
                    break;
            }*/
            tam = N-i+1;
            tamMax = 0;
            //tamMax = (tam>>1);
            // Busqueda binaria
            while(1)    {
                if(tam == tamMax+1)
                    break;
                int m = (tamMax + tam)>>1;
                if(i+m <= N)    {
                    int logtam = 0, dist=m, inicio=i, mi, ma;
                    while(dist >>= 1) logtam++;
                    mi = ST[inicio][logtam].first; 
                    ma = ST[inicio][logtam].second;
                    inicio = (inicio+m)-(1<<logtam); 
                    if(mi > ST[inicio][logtam].first)
                        mi = ST[inicio][logtam].first; 
                    if(ma < ST[inicio][logtam].second)
                        ma = ST[inicio][logtam].second;
                    if(ma-mi > k)  
                        tam = m;
                    else
                        tamMax = m;
                }
                else
                    tam = m;
            }
            ans += tamMax;
    }
    printf("%d",ans);
    free(vec);
    return 0;
}
