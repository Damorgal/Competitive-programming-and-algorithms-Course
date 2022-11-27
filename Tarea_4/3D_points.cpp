#include <iostream>
#include <math.h>
#include <vector>
#include <stdlib.h>

using namespace std;
void heapify(int **arr, int n, int i);
void heapSort(int **arr, int n);
void printArray(int **arr, int n);
double distancia(int **p, int a, int b);
int dmin_points(int **pts, int n);
void insert_qt(int **pts, int *qt, int posqt, int posi, int pos, int ax, int bx, int ay, int by);


int main()  {
	while(1)
	{
		// Realizamos el algoritmo hasta encontrar un 0
		int N;
		cin >> N;
		if(N == 0)
			break;

		// Leemos los puntos
		int **puntos;
    	puntos = new int*[10010];
    	for(int i=0; i<10000; i++)
     	   puntos[i] = new int[3];


		for(int i=0; i<N; i++)	{
			cin >> puntos[i][0];
			cin >> puntos[i][1];
			cin >> puntos[i][2];
		}

		// Ordenamos por X
		heapSort(puntos, N);

    	// Realizamos el problema
    	// La funcion dmin_points automaticamente elimina uno de los nodos involucrados
    	// Para así, al realizarlo 6 veces, encontremos las 6 distancias mínimas
    	double suma = 0;
    	for(int i=0; i<6; i++)
    		suma += dmin_points(puntos,N);

    	// Imprimimos la suma de las distancias
    	cout << suma;

    	// liberar memoria dinámica
    	for(int  i=0; i<10000; i++)
    	    delete[] puntos[i];
    	delete[] puntos;
    }
    return 0;
}

int dmin_points(int **pts, int n)	{
	// En la primera iteración, nos quedamos con la minima distancia de los 3 puntos mas cercanos respecto a x
	double dmin = distancia(pts,0,1);
	int posicion = 1;
	for(int i=2; i<4; i++)	{
		double aux = distancia(pts,0,i);
		if(dmin > aux)	{
			dmin = aux;
			posicion = i;
		}
	}
	// Creamos memoria para el quadtree
	int *qt = new int[(int)pow(4,n)];

	// Ahora realizamos el barrido
	for(int i=0; i<n; i++)	{
		int ind = 0;
		//vector<int> vec;
		for(int i=0; i<(int)pow(4,n); i++)
            qt[i] = -1;

        // Solo insertamos al QT los puntos con diferencia de coordenadas menor que dmin
		for(int j = i+1; 1; j++)	{
			if(i-j+i >= 0)
				if(pts[i][0]-pts[i-j+i][0] > dmin && abs(pts[i][1]-pts[i-j+i][1]) > dmin && abs(pts[i][2]-pts[i-j+i][2]) > dmin)
					if(ind == 1)
						break;
					else
						ind = 2;
			else
				ind = 2;

			if(j < n)
				if(pts[j][0]-pts[i][0] > dmin && abs(pts[j][1]-pts[i][1]) > dmin && abs(pts[j][2]-pts[i][2]) > dmin)
					if(ind == 2)
						break;
					else
						ind = 1;
			else
				ind = 1;

			if(ind != 2)
				insert_qt(pts,qt,0,i,i+i-j,-1000,1000,-1000,1000);
				//vec.push_back(i+i-j);
			if(ind != 1)
				insert_qt(pts,qt,0,i,j,-1000,1000,-1000,1000);
				//vec.push_back(j);
		}

		// Ahora actualizamos la distancia minima del quad tree
		if(dmin > distancia(pts,i,qt[0]))	{
			dmin > distancia(pts,i,qt[0]);
			posicion = qt[0];
		}

	}
	// Borramos el QT
	delete[] qt;

	// Eliminamos el nodo involucrado mandandolo lejos de los demás
	int del = (rand()%2001)-1000;
	del *=10000;
	pts[posicion][0] = pts[posicion][1] = pts[posicion][2] = del;

	return posicion;
}

void insert_qt(int **pts, int *qt, int posqt, int posi, int pos, int ax, int bx, int ay, int by)	{
	if(pts[pos][1] <= (ax+bx)/2)	{
		if(pts[pos][2] <= (ay+by)/2)	{
			int ps = posqt*4+3;
			if(qt[ps] == -1)
				qt[ps] = pos;
			else	{
				insert_qt(pts,qt,ps,posi,pos,ax,(ax+bx)/2,ay,(ay+by)/2);
				insert_qt(pts,qt,ps,posi,qt[ps],ax,(ax+bx)/2,ay,(ay+by)/2);
			}
			return;
		}

		else	{
			int ps = posqt*4+1;
			if(qt[ps] == -1)
				qt[ps] = pos;
			else	{
				insert_qt(pts,qt,ps,posi,pos,ax,(ax+bx)/2,(ay+by)/2,by);
				insert_qt(pts,qt,ps,posi,qt[ps],ax,(ax+bx)/2,(ay+by)/2,by);
			}
			return;
		}
	}
	else	{
		if(pts[pos][2] <= (ay+by)/2)	{
			int ps = posqt*4+4;
			if(qt[ps] == -1)
				qt[ps] = pos;
			else	{
				insert_qt(pts,qt,ps,posi,pos,(ax+bx)/2,bx,ay,(ay+by)/2);
				insert_qt(pts,qt,ps,posi,qt[ps],(ax+bx)/2,bx,ay,(ay+by)/2);
			}
			return;
		}
		else	{
			int ps = posqt*4+2;
			if(qt[ps] == -1)
				qt[ps] = pos;
			else	{
				insert_qt(pts,qt,ps,posi,pos,(ax+bx)/2,bx,(ay+by)/2,by);
				insert_qt(pts,qt,ps,posi,qt[ps],(ax+bx)/2,bx,(ay+by)/2,by);
			}
			return;
		}
	}
	qt[posqt] = qt[posqt*4+1];
	for(int i=2; i<=4; i++)	{
		int aux = qt[posqt*4+i];
		if(distancia(pts,posi,aux) < distancia(pts,posi,qt[posqt]))
			qt[posqt] = aux;
	}
}

double distancia(int **p, int a, int b)	{
	double x = pow(p[a][0]-p[b][0],2);
	double y = pow(p[a][1]-p[b][1],2);
	double z = pow(p[a][2]-p[b][2],2);
	return sqrt(x+y+z);
}

// To heapify a subtree rooted with node i which is
// an index in arr[]. n is size of heap
void heapify(int **arr, int n, int i)
{
    int largest = i; // Initialize largest as root
    int l = 2*i + 1; // left = 2*i + 1
    int r = 2*i + 2; // right = 2*i + 2

    // If left child is larger than root
    if (l < n && arr[l][0] > arr[largest][0])
        largest = l;

    // If right child is larger than largest so far
    if (r < n && arr[r][0] > arr[largest][0])
        largest = r;

    // If largest is not root
    if (largest != i)
    {
        swap(arr[i][0], arr[largest][0]);
        swap(arr[i][1], arr[largest][1]);
        swap(arr[i][2], arr[largest][2]);

        // Recursively heapify the affected sub-tree
        heapify(arr, n, largest);
    }
}

// main function to do heap sort
void heapSort(int **arr, int n)
{
    // Build heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // One by one extract an element from heap
    for (int i=n-1; i>=0; i--)
    {
        // Move current root to end
        swap(arr[0][0], arr[i][0]);
        swap(arr[0][1], arr[i][1]);
        swap(arr[0][2], arr[i][2]);

        // call max heapify on the reduced heap
        heapify(arr, i, 0);
    }
}

/* A utility function to print array of size n */
void printArray(int **arr, int n)
{
    for (int i=0; i<n; ++i)
        cout << arr[i][0] << " "<<arr[i][1]<<" "<<arr[i][2]<<endl;
}
