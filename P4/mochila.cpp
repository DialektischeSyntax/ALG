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
    vector<material> materiales;
    material m;
    cout<<endl<<endl;
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
        materiales.push_back(m);
    }
    file.close();
    m = {0, 0, 0};
    std::sort(materiales.begin(), materiales.end(), [&](const auto& m1, const auto& m2) { return m1.volumen < m2.volumen; });
    materiales.insert(materiales.begin(), m);
    vector<vector<int>> matriz(materiales.size());
    
    //Asignamos el tamaño correcto a la matriz
    for(int i = 0 ; i < materiales.size(); ++i)
    {
        matriz[i].resize(capacidad + 1);
    }

    //Inicializamos la primera columna a 0
    for(i = 0; i < materiales.size(); i++){
        matriz[i][0] = 0;
    }
    //Inicializamos la primera fila a 0
    for(i = 0; i < capacidad + 1; i++){
        matriz[0][i] = 0;
    }
    resolverMochila(capacidad, matriz, materiales);
    mostrarTabla(capacidad, matriz, materiales);
}

/*Resolución de la mochila teniendo los materiales ordenados por volumen y valorándolos en función de su precio.
  Si el material cabe en la mochila y su coste sumado al mejor camino que existía hasta la capacidad de la mochila - el volumen del material
  materiales[i].coste + matriz[i-1][j - materiales[i].volumen])es mejor que el mejor camino hasta ahora (matriz[i-1][j]) entonces el valor de matriz[i][j]
  será la suma que se ha evaluado en el bucle if. Si no, será el mejor camino hasta la fecha matriz[i-1][j]. Es decir, matriz[i][j] adopta el mayor valor entre
  los dos valores que se evalúan en el if, pues se busca la maximización del coste de la mochila.

  Si un material no cabe en la mochila se asigna a esa casilla el mejor valor hasta la fecha.
*/
void resolverMochila(int capacidad, vector<vector<int>> &matriz, vector<material> &materiales){

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
}

/*
mostrarTabla muestra la matriz o tabla para visualizar y entender la solución. Los dos primeros bucles for son para la muestra de la matriz, formateando la salida.
El siguiente es el que encuentra los materiales usados. El método utilizado es recorrer del final al principio la matriz de la solución, y teniendo en cuenta
que los materiales no se pueden repetir, cada vez que en una columna cambiaba un valor significaba que la casilla por donde se estaba iterando pertenecía a un material
usado. Entonces nos movíamos a la fila de antes, y tantas columnas a la izquierda como volumen tuviera el material y seguíamos iterando por la misma columna hacia atrás
hasta encontrar un valor diferente. Paramos cuando ya hubiéramos alcanzado toda la capacidad de la mochila o bien hubiésemos llegado al fin de la tabla.
*/

void mostrarTabla( int capacidad, vector<vector<int>> &matriz, vector<material> &materiales){
    cout<<endl<< "      ";

    for(int i = 0; i < capacidad + 1; i++){
        if(i < 10){
            cout << i << "   ";
        }
        else{
            cout << i << "  ";
        }
    }

    cout<<endl<<endl;

    for(int i = 0; i < materiales.size(); i++){
        if(materiales[i].volumen < 10){
            cout << materiales[i].volumen << "     ";
        }
        else{
            cout << materiales[i].volumen << "    ";
        }
        
        for(int j = 0; j < capacidad + 1; j++){
            if(matriz[i][j] > 9){
                cout<<matriz[i][j]<< "  ";
            }
            else{cout<<matriz[i][j]<< "   ";}
        }
        cout << endl;
    }

    cout<<endl;

    cout << "El coste final de la mochila es " << matriz[materiales.size()-1][capacidad] << ". Se han utilizado los materiales: "<<endl<<endl;
    int coste = 0, j = capacidad;
    for(int i = materiales.size() - 1; i > 0; i--){
            if(matriz[i][j] != matriz[i-1][j] && coste < capacidad){
                cout<< (materiales[i].etiqueta) << ", con volumen " << materiales[i].volumen <<" y coste " << materiales[i].coste << "."<<endl;
                j -= materiales[i].volumen;
                coste += materiales[i].volumen;
            }
    }
    cout<<endl;
}