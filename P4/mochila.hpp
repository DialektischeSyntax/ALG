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

void mochila();

void mostrarTabla(int capacidad, vector<vector<int>> &matriz, vector<material> &materiales);

void resolverMochila(int capacidad, vector<vector<int>> &matriz, vector<material> &materiales);

#endif
