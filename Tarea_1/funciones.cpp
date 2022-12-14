// Funciones hechas para la tarea de segment tree

// Hecho por Diego Aaron Moreno Galvan


void printArray(vector<int> arr)
{
	int n = arr.size();
    for (int i=0; i<n; i++)
        cout << arr[i] << " ";
    cout << endl;
    return;
}

void borra_vector(vector<vector<int>> &v)	{
	for(int i=0; i<v.size(); i++)
		v[i].clear();
	v.clear();
}

vector<int> lee_vector(char *dir) {
	int n, aux;
	vector<int> vec;
	ifstream file(dir); 
	
	file >> n >> aux;
	
	for(int i=0; i<n; i++)	{
		file >> aux;
		vec.push_back(aux);
	}
	
	file.close();
	return(vec);
}

vector<vector<int>> lee_preguntas(char *dir) {
	int n, aux, m;
	vector<vector<int>> vec;
	ifstream file(dir); 
	
	file >> aux >> n;
	
	vec.reserve(n);
	
	for(int i=0; i<aux; i++)
		file >> m;
	
	for(int i=0; i<n; i++)	{
		file >> aux; vec[i].push_back(aux);
		file >> aux; vec[i].push_back(aux);
		file >> aux; vec[i].push_back(aux);
	}
	
	file.close();
	return(vec);
}

vector<int> merge(vector<int> x, vector<int> y, const vector<int> &A)	{
	int coni = 0, cond = 0;
	vector<int> vec;
	int n_max = x.size()+y.size();
	for(int i=0; i<n_max; i++)	{
		if(coni < x.size())	{
			if(cond < y.size())	{
				if(A[x[coni]] <= A[y[cond]])	{
					vec.push_back(x[coni]);
					coni++;
				}
				else 	{
					vec.push_back(y[cond]);
					cond++;
				}
			}
			else 	{
				for(i = n_max; coni < x.size(); coni++)
					vec.push_back(x[coni]);
			}
		}
		else 	{
			for(i = n_max; cond < y.size(); cond++)
				vec.push_back(y[cond]);
		}
	}
	return vec;
}

void construye_seg_tree(vector<vector<int>> &t, const vector<int> &A, int pos, int a, int b)	{
	if(a == b)
		t[pos].push_back(b);
	else 	{
		int apos = 2*pos,  bpos = 2*pos+1;
		construye_seg_tree(t, A, apos, a, (int)((a+b)/2));
		construye_seg_tree(t, A, bpos, (int)((a+b)/2) + 1, b);
		vector<int> aux = merge(t[apos],t[bpos],A);
		t[pos] = aux;
	}
}

void traduce_seg_tree(vector<vector<int>> &t, const vector<int> &A, int pos, int a, int b)	{
	if(a == b)
		t[pos][0] = A[t[pos][0]];
	else 	{
		int apos = 2*pos,  bpos = 2*pos+1;
		for(int i=0; i<t[pos].size(); i++)
			t[pos][i] = A[t[pos][i]];
		traduce_seg_tree(t, A, apos, a, (int)((a+b)/2));
		traduce_seg_tree(t, A, bpos, (int)((a+b)/2) + 1, b);
	}
}

void busqueda_binaria(const vector<int> vec, int k, int a, int b, int &indicador)	{
	if(indicador != -1)
		return;
	int con = 0;
	for(int i=0; i<vec.size(); i++)
		if(vec[i]<=b)
			con++;

	if(con >= k && a!=b)	{
		busqueda_binaria(vec, k, a, (int)((a+b)/2), indicador);
		busqueda_binaria(vec, k, (int)((a+b)/2)+1, b, indicador);
	}
	else 	{
		if(con == k && a == b)
			indicador = b;
	}
}

void st_rmq(vector<vector<int>> &t, const vector<int> &A, vector<int> &vec, int pos, int a, int b, int i, int j)	{
	if(i>b || j<a) 
		return;
	if(i<=a && b<=j) 	{
		for(int ind=0; ind<t[pos].size(); ind++)
			vec.push_back(t[pos][ind]);
		return;
	}
	st_rmq(t, A, vec, 2*pos, a, (int)((a+b)/2), i, j);
	st_rmq(t, A, vec, 2*pos+1, (int)((a+b)/2)+1, b, i, j);
}

int st_rmq(vector<vector<int>> &t, const vector<int> &A, int i, int j, int k)	{
	vector<int> vec;
	st_rmq(t, A, vec, 1, 0, (int)A.size()-1, i-1, j-1);
	if(k > (int)vec.size())	{cout<<"Error, k es mayor al rango de n??meros"<<endl; return -1;}
	int indicador = -1;
	busqueda_binaria(vec,k,0,A.size()-1,indicador);
	return indicador;
}

void responde_preguntas(vector<vector<int>> &vec, const vector<vector<int>> &preg, const vector<int> &arr, const vector<int> &traductor)	{
	int m=preg.size();
	for(int i=0; i<m; i++)	{
		int min_indice = st_rmq(vec, arr, preg[i][0], preg[i][1], preg[i][2]);
		int min_valor;
		for(min_valor=0; traductor[min_valor]!=min_indice; min_valor++);
		
		int min = arr[min_valor];
		cout << min<<endl;
	}
	
}
