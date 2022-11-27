// Funciones hechas para la tarea de segment tree

// Hecho por Diego Aaron Moreno Galvan

#include <iostream>
#include <fstream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
#include <gsl/gsl_math.h>

using namespace std;

void printArray(vector<int> arr);
void borra_vector(vector<vector<int>> &v);
vector<int> lee_vector(char *dir);
vector<vector<int>> lee_preguntas(char *dir);
void responde_preguntas(vector<vector<int>> &vec, const vector<vector<int>> &preg, const vector<int> &arr, const vector<int> &traductor);
vector<int> merge(vector<int> x, vector<int> y, const vector<int> &A);
void construye_seg_tree(vector<vector<int>> &t, const vector<int> &A, int pos, int a, int b);
void traduce_seg_tree(vector<vector<int>> &t, const vector<int> &A, int pos, int a, int b);
void busqueda_binaria(const vector<int> vec, int k, int a, int b, int &indicador);
void st_rmq(vector<vector<int>> &t, const vector<int> &A, vector<int> &vec, int pos, int a, int b, int i, int j);
int st_rmq(vector<vector<int>> &t, const vector<int> &A, int i, int j, int k);

#include "funciones.cpp"
