#include <fstream>
#include <cstdio>
#include <iostream>
#include <vector>
#include <string>
#include <unistd.h>
#include <algorithm>
#include <math.h>

#ifndef CAMBIO_HPP
#define CAMBIO_HPP

using namespace std;

void cambio(int opt);

void devolverCambio(int cambio, vector<vector<float>> matriz, vector<float> &sistemaMonetario);

void ordenar(vector<float> &sistemaMonetario);

void mostrarTabla( int cambio, vector<vector<float>> matriz, vector<float> &sistemaMonetario);

void devolverCambioLimitado(vector<int> &cantidad, int cambio, vector<float> &sistemaMonetario, vector<vector<float>> matriz);

#endif