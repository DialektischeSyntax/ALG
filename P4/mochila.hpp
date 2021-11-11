#include <fstream>
#include <cstdio>
#include <iostream>
#include <vector>
#include <string>
#include <unistd.h>
#include <algorithm>
#ifndef MOCHILA_HPP
#define MOCHILA_HPP

using namespace std; 

struct material;

void mochilaDinamica();

void ordenar(vector<material> &materiales);

void mostrarTabla(int capacidad, int cantidad, vector<vector<int>> matriz);

void resolverMochila(int capacidad, int cantidad, vector<vector<int>> matriz, vector<material> &materiales);

void Quicksort(vector<material> &materiales, int start, int end );

int Partition(vector<material> &materiales, int start, int end );



#endif
