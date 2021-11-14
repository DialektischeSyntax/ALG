#include "mochila.hpp"

using namespace std;

struct material {
    int etiqueta;
    int volumen;
    int coste;
};

void mochila(){
    string etiqueta, volumen, coste;
    int i = 0;
    int capacidad;
    vector<material> vMaterials;
    material m;
    cout << "Introduzca la capacidad de la mochila"<<endl;
    cin>>capacidad;
    cin.ignore();
    cout<<endl;
    fstream file;
    file.open("materialesmochila.txt", std::ios::in);
    while(getline(file, etiqueta, ',')){
        getline(file, volumen, ',');
        getline(file, coste);
        m.etiqueta = stoi(etiqueta);
        m.volumen = stoi(volumen);
        m.coste = stoi(coste);
        vMaterials.push_back(m);
    }
    file.close();
    m = {0, 0, 0};
    ordenar(vMaterials);
    vMaterials.insert(vMaterials.begin(), m);
    vector<vector<int>> matriz(vMaterials.size());
    for(int i = 0 ; i < vMaterials.size(); ++i)
    {
        matriz[i].resize(capacidad + 1);
    }
    for(i = 0; i < vMaterials.size(); i++){
        matriz[i][0] = 0;
    }
    // Inicialización de todas las columnas en cero
    for(i = 0; i < capacidad + 1; i++){
        matriz[0][i] = 0;
    }
    resolverMochila(capacidad, matriz, vMaterials);
    //mostrarTabla(capacidad, matriz, vMaterials);
}

void ordenar(vector<material> &materiales)
{
    int j, i = 0;
    material aux;
    while(i < materiales.size()){
        for(j=0 ; j < materiales.size()-1; j++ )
        {
            if(materiales[j].volumen > materiales[j+1].volumen)
            {
                aux = materiales[j];
                materiales[j] = materiales [j+1];
                materiales[j+1] = aux;
            }
        }
        i++;
    }
}

void resolverMochila(int capacidad, vector<vector<int>> matriz, vector<material> &materiales){

    for(int i = 1; i < materiales.size(); i++){
        for(int j = 1; j < capacidad + 1; j++){
            if(materiales[i].volumen <= j){
                if((materiales[i].coste + matriz[i-1][j - materiales[i].volumen]) > matriz[i-1][j]){
                    matriz[i][j] = materiales[i].coste + matriz[i-1][j - materiales[i].volumen];
                }
                else{ matriz[i][j] = matriz[i-1][j]; }
            }
            else{ matriz[i][j] = matriz[i-1][j]; }
        }
    }

    for(int i = 0; i < materiales.size(); i++){
        for(int j = 0; j < capacidad + 1; j++){
            if(matriz[i][j] > 9){
                cout<<matriz[i][j]<< "  ";
            }
            else{cout<<matriz[i][j]<< "   ";}
        }
        cout << endl;
    }
}

void mostrarTabla( int capacidad, vector<vector<int>> matriz, vector<material> &materiales){
    for(int i = 0; i < materiales.size(); i++){
        for(int j = 0; j < capacidad + 1; j++){
            cout<<matriz[i][j]<< " ";
        }
        cout << endl;
    }
}