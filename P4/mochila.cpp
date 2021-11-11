#include "mochila.hpp"

using namespace std;

struct material {
    int etiqueta;
    int volumen;
    int coste;
};

void mochilaDinamica(){
    string etiqueta, volumen, coste;    
    vector<material> materiales;
    materiales.clear();
    int i,j,capacidad, cantidad = 0;
    cout << "Introduzca la capacidad de la mochila: " << endl;
    cin>>capacidad;
    cin.ignore();
    cout <<"flag 0";
    cout<<endl;
    fstream file;
    material m;
    file.open("materialesmochila.txt", std::ios::in);
    while(getline(file, etiqueta, ',')){
        getline(file, volumen, ',');
        getline(file, coste);
        cout<<"leyendo"<<endl;
        m.etiqueta = stoi(etiqueta);
        m.volumen = stoi(volumen);
        m.coste = stoi(coste);
        materiales.push_back(m);
        cantidad++;
        cout<<cantidad<<endl;
    }
    cout<<"ha salido del bucle"<<endl;
    file.close();
    cout << "flag 1"<<endl;
    // creamos la matriz que nos hará de tabla.
    vector<vector<int>> matriz(cantidad);
    cout<<"ha creado el vector"<<endl;
    for(int i = 0 ; i < cantidad + 1; ++i)
    {
        cout<<"haciendo el resize"<<endl;
        //Grow Columns by n
        matriz[i].resize(capacidad + 1);
    }
    m = {0, 0, 0};

    materiales.insert(materiales.begin(), m);

    cout<<"ha salido del resize"<<endl;
    for(int i = 0; i < materiales.size(); i++){
        cout<<materiales[i].etiqueta<<", "<<materiales[i].volumen<<", "<<materiales[i].coste<<endl;
    }
    //materiales = {{0,34,1}, {1,21,6}, {12,1,7}, {2,4,6}};
    sort(materiales.begin(), materiales.end(), [&](const auto& m1, const auto& m2) { return m1.volumen < m2.volumen; });
    //ordenar(materiales);
    //Quicksort(materiales, 0, materiales.size() - 1);
    cout << "Flag 2";
    //inicialización de las filas a 0
    for(i = 0; i < materiales.size(); i++){
        matriz[i][0] = 0;
    }
    // Inicialización de todas las columnas en cero
    for(i = 0; i < capacidad + 1; i++){
        matriz[0][i] = 0;
    }
    resolverMochila(capacidad, cantidad, matriz, materiales);
    mostrarTabla(capacidad, cantidad, matriz);
}
    


//mochila de 6 objetos. cada objeto es una fila.
//cada columna representa la capacidad de la mochila ascendentemente.
//se ordenan por volumen. si el objeto no cabe en la mochila, se deja 
//el valor que tenía (se inicializa a 0 la matriz por si se da el caso.)
//si el objeto cabe, se comprueba si su valor es mayor al que tenía.

//hay que averiguar como hacer las combinaciones
//de varios objetos para cierto volumen.
//Por ejemplo, que se de el caso de que el objeto de volumen 7 tenga menos valor
//que la combinación de los objetos con volumen 1 y 6.

//Hay que seguir comprobando si el tamaño del material es más pequeño (o igual)
//al de la mochila ya que la mochila puede estar medio llena y que no quepa en ese momento
//pero que fuera mejor posibilidad meter dicho objeto. Hacer continuas comprobaciones hasta llegar
//a un objeto que tenga mayor volumen que la mochila. Una vez esto ocurra aumentamos
//la iteración hacia un volumen mayor en la mochila, ya habríamos explorado las posibilidades 
//para ese volumen de la mochila.

void resolverMochila(int capacidad, int cantidad, vector<vector<int>> matriz, vector<material> &materiales){

    for(int i = 0; i < materiales.size(); i++){
        cout<<materiales[i].etiqueta<<", "<<materiales[i].volumen<<", "<<materiales[i].coste<<endl;
    }
    
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

void mostrarTabla( int capacidad, int cantidad, vector<vector<int>> matriz){
    for(int i = 0; i < cantidad + 1; i++){
        for(int j = 0; j < capacidad + 1; j++){
            cout<<matriz[i][j]<< " ";
        }
        cout << endl;
    }
}

void ordenar(vector<material> &materiales)
	{
	int j, i = 0;
    material aux;
	cout<< "vector size is "<<materiales.size()<<endl;
	while(i < materiales.size()){
        for(j=0 ; j < materiales.size() - 1; j++ )
		{
            cout<<"sorting..."<<endl;
			if(materiales[j].volumen > materiales[j+1].volumen)
			{
                aux = materiales[j];
                materiales[j] = materiales [j+1];
                materiales[j+1] = aux;
			}
		}
        i++;
        cout<<"iterated"<<endl;
    }
    cout << "sorting ended.";
}

/*int main()
{
    vector<material> vMaterials = {{0,34,1}, {1,21,6}, {12,1,7}, {2,4,6}};
    ordenar(vMaterials);
    cout << "\n";
    for (auto& v : vMaterials)
        cout << v.volumen << "\n";
}
*/