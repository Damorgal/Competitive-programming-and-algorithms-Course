#include <iostream>
#include <math.h>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include <fstream>

using namespace std;

int max_N = 100000;		// Número máximo de memoria del vector que contiene al árbol, claramente puedes modificar aquí

vector<int> crea_arbol();
void crea_arbol(vector<int> &t, int pos, int N);
vector<int> lee_arbol(char *s);
int LCA(vector<int> &t, int x, int y);
int LCA(int *P, int *L, int x, int y);
void niveles(vector<int> &t, int *L, int h, int pos);
void padres(vector<int> &t, int *P, int p, int pos);
int LCA_jumper(vector<int> &t, int x, int y);
void jump_pointers(vector<int> &t, int *P, int k, int pos);
int LCA_ladder(int *P, int *Long, int *L, int x, int y);
int LCA_ladder(vector<int> &t, int x, int y);
void ladder_pointers(vector<int> &t, int *P, int *L, int pos);
void long_path(vector<int> &t, int *L, int l, int pos);
int LCA_hybrid(int *P1, int *P2, int *Long, int *L, int x, int y);
int LCA_hybrid(vector<int> &t, int x, int y);


int main()  {
    // Para crear un arbol cualquiera y salvarlo en un txt después...
    /*
    vector<int> vec = crea_arbol();
    ofstream fs("arbol.txt");
    for(int i=1; i<max_N; i++)
    	fs << vec[i] << " ";
    fs.close();
    for(int i=1; i<500; i++)
    	cout << vec[i] << " ";
    */


    // Para leer un arbol ya creado, y realizar el LCA con nodos que deseamos

    vector<int> vec = lee_arbol("arbol.txt");
    for(int i=1; i<max_N; i++)
        cout << vec[i] << " ";
    cout<<endl;

    // Indices deseados
    int u = 8;
    int v = 20;
    cout<<"vec["<<u<<"] : "<<vec[u]<<endl<<"vec["<<v<<"] : "<<vec[v]<<endl;

    // LCA noramal de orden O(N)
    int aux = LCA(vec,u,v);
    cout<<"LCA_O(N) = "<<"vec["<<aux<<"] : "<<vec[aux]<<endl;

    // LCA con Jump Pointers O(logN)
    aux = LCA_jumper(vec,u,v);
    cout<<"LCA_jump = "<<"vec["<<aux<<"] : "<<vec[aux]<<endl;

    // LCA con Ladder decomposition.
    aux = LCA_ladder(vec,u,v);
    cout<<"LCA_ladder= "<<"vec["<<aux<<"] : "<<vec[aux]<<endl;

    // LCA con híbrido entre jump y ladder O(1)
    aux = LCA_hybrid(vec,u,v);
    cout<<"LCA_hybrid= "<<"vec["<<aux<<"] : "<<vec[aux]<<endl;

    return 0;
}

int LCA_hybrid(vector<int> &t, int x, int y)	{
	int P_jump[max_N];
	jump_pointers(t,P_jump,1,1);
	int L[max_N];
	niveles(t,L,0,1);
	int Long[max_N];
	long_path(t,Long,1,1);
	int P_ladder[max_N];
	ladder_pointers(t,P_ladder,Long,1);
	return LCA_hybrid(P_jump,P_ladder,Long,L,x,y);
}

int LCA_hybrid(int *P1, int *P2, int *Long, int *L, int x, int y)	{
	//Hacemos un Jump
	if(P1[x] != P1[y])	{
		if(L[x] > L[y])
			x = P1[x];
		else
			y=P1[y];
	}
	// Realizamos el algoritmo de ladder
	return LCA_ladder(P2,Long,L,x,y);
}

void long_path(vector<int> &t, int *L, int l, int pos)	{
	if(t[pos] == -1 || pos >= max_N)		{
		if(pos < max_N)
			L[pos] = -1;
		return;
	}
	L[pos] = l;
	long_path(t,L,l+1,pos*2);
	long_path(t,L,l+1,pos*2+1);
	if(pos*2 < max_N)	{
		if(L[pos*2] > L[pos] && L[pos*2] >= L[pos*2+1])	{
			L[pos] = L[pos*2];
			long_path(t,L,1,pos*2+1);
		}
		else if(L[pos*2+1] > L[pos] && L[pos*2+1] >= L[pos*2])	{
			L[pos] = L[pos*2+1];
			long_path(t,L,1,pos*2);
		}
	}
}

void ladder_pointers(vector<int> &t, int *P, int *L, int pos)	{
	if(t[pos] == -1 || pos>=max_N)
		return;
	else	{
		int aux = pos;
		for(int i=0; i<2*L[pos] && aux != 1; aux /= 2);
		P[pos] = aux;
		ladder_pointers(t,P,L,pos*2);
		ladder_pointers(t,P,L,pos*2+1);
	}
}

int LCA_ladder(vector<int> &t, int x, int y)	{
	int Long[max_N];
	long_path(t,Long,1,1);
	int P[max_N];
	ladder_pointers(t,P,Long,1);
	int L[max_N];
	niveles(t,L,0,1);
	return LCA_ladder(P,Long,L,x,y);
}

int LCA_ladder(int *P, int *Long, int *L, int x, int y)	{
	while(Long[P[x]] != Long[P[y]])	{
		x = P[x];
		y = P[y];
	}
	while(x != y)	{
		if(L[x] > L[y])
			x /= 2;
		else
			y /= 2;
	}
	return x;
}

int LCA_jumper(vector<int> &t, int x, int y)	{
	int P[max_N];
	jump_pointers(t,P,1,1);
	int L[max_N];
	niveles(t,L,0,1);
	return LCA(P,L,x,y);
}

void jump_pointers(vector<int> &t, int *P, int k, int pos)	{
	if(t[pos] == -1 || pos>=max_N)
		return;
	else	{
		int con = floor(log2(k));
		int aux = pos;
		for(int i=0; i<con; i++)
			aux = aux/2;
		P[pos] = aux;
		jump_pointers(t,P,k+1,pos*2);
		jump_pointers(t,P,k+1,pos*2+1);
	}
}

int LCA(vector<int> &t, int x, int y)	{
	int L[max_N];
	niveles(t,L,0,1);
	int P[max_N];
	padres(t,P,0,1);
	return LCA(P,L,x,y);
}

int LCA(int *P, int *L, int x, int y)	{
	while(P[x] != P[y])	{
		if(L[x] > L[y])
			x = P[x];
		else
			y=P[y];
	}
	while(x != y)	{
		if(L[x] > L[y])
			x = P[x];
		else
			y = P[y];
	}
	return x;
}

void padres(vector<int> &t, int *P, int p, int pos)	{
	if(t[pos] == -1 || pos>=max_N)
		return;
	else	{
		P[pos] = p;
		padres(t,P,pos,pos*2);
		padres(t,P,pos,pos*2+1);
	}
}

void niveles(vector<int> &t, int *L, int h, int pos)	{
	if(t[pos] == -1 || pos>=max_N)
		return;
	else	{
		L[pos] = h;
		niveles(t,L,h+1,pos*2);
		niveles(t,L,h+1,pos*2+1);
	}
}

vector<int> crea_arbol()	{
	int N = max_N;
	vector<int> t;
	t.reserve(N);
	srand(time(NULL));
	crea_arbol(t,1,N);
	return t;
}

void crea_arbol(vector<int> &t, int pos, int N)	{
	if(pos >= N) return;
	if(pos == 1){
		t[pos] = rand()%501;	// Colocamos en el vector números de 0 a 500
		max_N = 2;
	}
	else	{
		if(rand()%2 == 0)	{
			t[pos] = rand()%501;
			max_N = pos+1;
		}
		else
			t[pos] = -1;		// Señalamos con un -1 para indicar que no hay nada en ese nodo
	}
	if(t[pos] != -1)	{
		crea_arbol(t,pos*2,N);
		crea_arbol(t,pos*2+1,N);
	}
	else return;
}

vector<int> lee_arbol(char *s)  {
    vector<int> v;
    int aux;
    v.push_back(0);
    ifstream fe(s);
    for(max_N=0; !fe.eof(); max_N++) {
        fe >> aux;
        v.push_back(aux);
    }
    fe.close();
    return v;
}
