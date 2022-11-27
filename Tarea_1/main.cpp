// Programa principal para tarea 1 programacion avanzada
// Encontrar k-esimo minimo dentro de un rango de índices del arreglo
// Para resolverlo se usa la estructura de datos de segment tree

#include "funciones.hpp"

 
int main(int narg, char **varg)	{
	vector<int> arr;
	vector<vector<int>> vec; 
	vector<vector<int>> preguntas;
	
	/** Para leer desde consola **/
	/*
	int n, m, aux;
	cin>>n>>m;
	for(int i=0; i<n; i++)	{
		cin>>aux;
		arr.push_back(aux);
	}
	preguntas.reserve(m);
	for(int i=0; i<m; i++)	{
		cin>>aux; preguntas[i].push_back(aux);
		cin>>aux; preguntas[i].push_back(aux);
		cin>>aux; preguntas[i].push_back(aux);
	}
	*/
	
	/** Para leer desde archivo .txt **/
	arr = lee_vector(varg[1]);
	preguntas = lee_preguntas(varg[1]);
    
    /** Pedimos memoria para el segment tree**/
    // Altura que tendrá el segment tree
    int x = (int)(ceil(log2(arr.size()))); 
    // Máximo número de nodos que tiene el s. tree
    int max_size = 2*(int)pow(2, x)-1; 
    vec.reserve(max_size);
    
    /** Construimos el segment tree **/
    construye_seg_tree(vec, arr, 1, 0, (int)arr.size()-1);
    vector<int> traductor; traductor.reserve(arr.size());
    for(int i=0; i<(int)arr.size(); i++)
		traductor[vec[1][i]] = i;
    traduce_seg_tree(vec,traductor,1,0,arr.size()-1);
 
    /** Respondemos preguntas **/
    responde_preguntas(vec,preguntas,arr,traductor);
    
    return 0;
}
