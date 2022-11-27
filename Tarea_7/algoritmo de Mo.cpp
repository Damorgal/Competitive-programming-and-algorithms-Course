#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

int T,N,M,Q,posA,posB;
int comp = 0;
int representantes[1000000];
void Qsort(int *pts[], int a, int b);

void components(int *graf[], int a, int b)  {
    int i,j;
    for(i=0; graf[i][0]<a && graf[i][1]<a && i<M; i++);
    posA=i;
    for(; graf[i][0]<=b && graf[i][1]<=b && i<M; i++)  {
        if(representantes[graf[i][0]] != representantes[graf[i][1]]) {
            comp--;
            for(j=0; j<N; j++)
                if(representantes[j]==graf[i][1])
                    representantes[j]=graf[i][0];
        }
    }
    posB=i;
}

void inserta(int *graf[], int b)  {
    int i,j;
    for(i=posB; graf[i][0]<=b && graf[i][1]<=b && i<M; i++)  {
        if(representantes[graf[i][0]] != representantes[graf[i][1]]) {
            comp--;
            for(j=0; j<N; j++)
                if(representantes[j]==graf[i][1])
                    representantes[j]=graf[i][0];
        }
    }
    posB=i;
}

void quita(int *graf[], int a, int b)  {
    int i,j;
    for(i=posA; graf[i][0]<a && graf[i][1]<a && i<M; i++);
    posA=i;
    comp=N;
    for(int j=0; j<N; j++)
        representantes[j]=j;
    for(; graf[i][0]<=b && graf[i][1]<=b && i<M; i++)  {
        if(representantes[graf[i][0]] != representantes[graf[i][1]]) {
            comp--;
            for(j=0; j<N; j++)
                if(representantes[j]==graf[i][1])
                    representantes[j]=graf[i][0];
        }
    }
    posB=i;
}

int main()  {
    ios_base::sync_with_stdio(0);cin.tie(0);
    scanf("%d",&T);
    for(int i=0; i<T; i++)  {
        scanf("%d %d %d",&N,&M,&Q);
        //Modificamos el numero de componentes y los representante
        comp=N;
        for(int j=0; j<N; j++)
            representantes[j]=j;
        //Creamos memoria para guardar las aristas y las queries
        int **graf=(int**)malloc(sizeof(int*)*M);
        for(int j=0; j<M; j++) graf[j] = (int*)malloc(sizeof(int)*2);
        int **queries=(int**)malloc(sizeof(int*)*Q);
        for(int j=0; j<Q; j++) queries[j] = (int*)malloc(sizeof(int)*2);
        //Leemos las aristas y las queries
        for(int j=0; j<M; j++)
            scanf("%d %d",&graf[j][0],&graf[j][1]);
        for(int j=0; j<Q; j++)
            scanf("%d %d",&queries[j][0],&queries[j][1]);
        //Ordenamos
        Qsort(queries,0,Q-1);
        Qsort(graf,0,M-1);
        cout<<queries[0][0]<<" -> "<<queries[0][1]<<endl;

        components(graf,queries[0][0],queries[0][1]);
        printf("%d\n",comp);
        for(int j=1; j<Q; j++)  {
            if(queries[j][0]==queries[j-1][0])
                inserta(graf,queries[j][1]);
            else
                quita(graf,queries[j][0],queries[j][1]);
            printf("%d\n",comp);
        }

        for(int j=0; j<M; j++) free(graf[j]);
        free(graf);
        for(int j=0; j<Q; j++) free(queries[j]);
        free(queries);
    }
    return 0;
}

void Qsort(int *pts[], int a, int b)	{
	if(b<=a)
		return;
	else	{
		//Eleccion de pivote
		int pivote = pts[b][0];
		//Reposicionamiento de pivote
		int i=a, j=b;
		for(; i<j; i++, j--)	{
			if(pts[i][0] > pivote && pts[j][0] < pivote)	{
				int *aux = pts[i];
				pts[i] = pts[j];
				pts[j] = aux;
			}
		}
		pivote = i; //Indice del numero pivote
		//Realizamos el algoritmo
		i=a; j=b;
		while(i<j)	{
			for(; pts[i][0] < pts[pivote][0]; i++);
			for(; pts[j][0] > pts[pivote][0]; j--);
			if(i!=pivote && j!=pivote)	{
				int *aux = pts[i];
				pts[i] = pts[j];
				pts[j] = aux;
			}
			else	{
				if(i==pivote && j==pivote)
					break;
				if(pts[i][0]!=pts[j][0])	{
					if(i==pivote)	{
						int *aux = pts[i];
						pts[i] = pts[j];
						pts[j] = aux;
						pivote = j;
					}
					else	{
						int *aux = pts[i];
						pts[i] = pts[j];
						pts[j] = aux;
						pivote = i;
					}
				}
				else	{
					if(i==pivote)   {
                        if(pts[i][1]>pts[j][1]) {
                            int *aux = pts[i];
                            pts[i] = pts[j];
                            pts[j] = aux;
                            pivote = j;
                            i++;
                        }
                        else j--;
					}
					else    {
                        if(pts[i][1]>pts[j][1]) {
                            int *aux = pts[i];
                            pts[i] = pts[j];
                            pts[j] = aux;
                        }
                        i++;
					}
				}
			}
		}
		Qsort(pts,pivote+1,b);
		Qsort(pts,a,pivote-1);
	}
}
