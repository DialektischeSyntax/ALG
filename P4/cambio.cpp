#include "cambio.hpp"
using namespace std;


void cambio(int opt){

    float inf = INFINITY;
    int cambio, moneda, i = 0;
    string cadena;
    cout<<endl<<endl;
    cout<<"elija el tipo:"<<endl<<endl;
    cout<<"1. Monedas y billetes ilimitados"<<endl<<endl;
    cout<<"2. Monedas y billetes limitados. Usted introduce la cantidad de cada tipo."<<endl<<endl;
    cin>>opt;
    vector<float> sistemaMonetario;
    fstream file;
    file.open("sistemasmonetarios.txt", std::ios::in);
    while(getline(file, cadena, ',')){
        moneda = stoi(cadena);
        sistemaMonetario.push_back(moneda);
    }
    file.close();
    sistemaMonetario.insert(sistemaMonetario.begin(), 0);
    ordenar(sistemaMonetario);
    if(opt == 1){
        /*for (auto& v : sistemaMonetario)
        cout << v << "\n";
        */
        cout<<endl<<endl;
        cout<<"Introduzca el cambio"<<endl;
        cin>>cambio;
        cin.ignore();
        cout<<endl;
        vector<vector<float>> matriz(sistemaMonetario.size());
            for(int i = 0 ; i < sistemaMonetario.size(); ++i)
        {
            matriz[i].resize(cambio + 1);
        }
        for(i = 0; i < cambio + 1; i++){                //Inicialización de la primera fila a inf.
            matriz[0][i] = inf;
        }
        for(i = 0; i < sistemaMonetario.size(); i++){   //Inicialización de la primera columna a 0.
            matriz[i][0] = 0;
        }
            devolverCambio(cambio, matriz, sistemaMonetario);
        }

    else if (opt == 2){
        vector<int> cantidad;
        cantidad.resize(sistemaMonetario.size());
        int dinero = 0, j = cambio = 0;
        cantidad[0] = 0;
        cout<<endl;
        cout<<"Introduzca el cambio:"<<endl;
        cin>>cambio;
        cin.ignore();
        cout<<endl;
        for(int i = 1; i < sistemaMonetario.size(); i++){
            if(sistemaMonetario[i] > 200){
                cout<<"Introduzca la cantidad de billetes de " << (sistemaMonetario[i] / 100) <<" euros disponible:"<<endl;
                cin >> dinero;
                cin.ignore();
                cantidad[i] = dinero;
            }
            else if(sistemaMonetario[i] == 200 || sistemaMonetario[i] == 100){
                cout<<"Introduzca la cantidad de monedas de " << (sistemaMonetario[i] / 100) <<" euros disponible:"<<endl;
                cin >> dinero;
                cin.ignore();
                cantidad[i] = dinero;
                }
            else{cout<<"Introduzca la cantidad de monedas de " << sistemaMonetario[i] <<" centimos disponible:"<<endl;
                cin >> dinero;
                cin.ignore();
                cantidad[i] = dinero;
            }
        }
        vector<vector<float>> matriz(sistemaMonetario.size());
        for(int i = 0 ; i < sistemaMonetario.size(); ++i)
        {
            matriz[i].resize(cambio + 1);
        }
        for(i = 0; i < cambio + 1; i++){                //Inicialización de la primera fila a inf.
            matriz[0][i] = inf;
        }
        for(i = 0; i < sistemaMonetario.size(); i++){   //Inicialización de la primera columna a 0.
            matriz[i][0] = 0;
        }
        cout<<endl<<endl;
        devolverCambioLimitado(cantidad, cambio, sistemaMonetario, matriz);
        mostrarTabla(cantidad, cambio, sistemaMonetario, matriz);
    }
    
    /*
    reservar(cambio, sistemaMonetario);
        //reserva de memoria para la matriz.
    ordenar(sistemaMonetario);
    devolverCambio(cambio, matriz, sistemaMonetario);
    //mostrarTabla(cambio, matriz, sistemaMonetario);
    */
}

//Ordenación burbuja del sistema monetario leído por el fichero.
//No sé si puedo usar std::sort así que implementé burbuja que no es lo más eficiente pero se implementa rápido.

void ordenar(vector<float> &sistemaMonetario)
{
    int j, i = 0;
    int aux;
    while(i < sistemaMonetario.size()){
        for(j=0 ; j < sistemaMonetario.size()-1; j++ )
        {
            if(sistemaMonetario[j] > sistemaMonetario[j+1])
            {
                aux = sistemaMonetario[j];
                sistemaMonetario[j] = sistemaMonetario [j+1];
                sistemaMonetario[j+1] = aux;
            }
        }
        i++;
    }
}

void devolverCambio(int cambio, vector<vector<float>> matriz, vector<float> &sistemaMonetario){

    //En esta primera parte resuelvo el problema del cambio. El procedimiento es sencillo, basándonos en el principio de 
    //optimalidad lo único que cambia respecto a la mochila es que se pueden repetir los objetos (monedas), así que
    //en vez de movernos por la anterior fila para comprobar el mejor camino o combinación, podemos movernos por la actual fila
    //por lo que solo cambia la columna, como se puede comprobar en el bucle. Partimos dese columna y fila 1 no 0 porque
    //los primeros elementos son 0 e inf.

    //Si con la moneda que estamos valorando no es posible devolver un cambio exacto, entonces el valor de la casilla será infinito.
    //De todas formas con el sistema monetario europeo es imposible porque hay monedas de 1 céntimo.
    
    float inf = INFINITY;
    for(int i = 1; i < sistemaMonetario.size(); i++){
        for(int j = 1; j < cambio + 1; j++){
            if(sistemaMonetario[i] <= j){
                if((1 + matriz[i][j - sistemaMonetario[i]])< matriz[i-1][j]){
                    matriz[i][j] = 1 + matriz[i][j - sistemaMonetario[i]];
                }
                else{ matriz[i][j] = matriz[i-1][j]; }
            }
            else{ matriz[i][j] = matriz[i-1][j]; }
        }
    }

    cout<<endl<< "         ";

    for(int i = 0; i < cambio + 1; i++){
        if(i < 10){
            cout << i << "    ";
        }
        else{
            cout << i << "   ";
        }
    }

    cout<<endl<<endl;

    //Este bucle es para mostrar la tabla, es una variante de la función mostrarTabla() que no he podido usar porque he tenido
    //problemas pasando la matriz por referencia, así que imprimo la tabla directamente en la misma función donde se resuelve el
    //problema.

    for(int i = 0; i < sistemaMonetario.size(); i++){
        if(sistemaMonetario[i] < 10){
            cout << sistemaMonetario[i] << "        ";
        }
        else if(sistemaMonetario[i] < 100){
            cout << sistemaMonetario[i] << "       ";
        }
        else if(sistemaMonetario[i] < 1000){
            cout << sistemaMonetario[i] << "      ";
        }
        else if(sistemaMonetario[i] < 10000){
            cout << sistemaMonetario[i] << "     ";
        }
        else{
            cout << sistemaMonetario[i] << "    ";
        }
        for(int j = 0; j < cambio + 1; j++){

            if(matriz[i][j] == inf){
                cout<<matriz[i][j]<< "  ";
            }
            else if(matriz[i][j] > 9){
                cout<<matriz[i][j]<< "   ";
            }
            else {cout<<matriz[i][j]<< "    ";}
        }
        cout << endl << endl;
    }

    cout<<endl;
    // Con este bucle recorremos la matriz de forma óptima buscando las monedas que se han usado e imprimiéndolas en pantalla.
    // Las encontramos cuando, recorriendo la matriz del final al principio, encontramos un cambio en la columna que recorremos,
    // ya que el último valor de cada columna es el óptimo. En la fila donde se produce el cambio se encuentra el valor de la moneda
    // que se ha introducido en la mochila, entonces nos movemos hacia la izquierda en la tabla tantas veces como valor tenga esa moneda
    // y procedemos otra vez igual, así hasta que lleguemos hasta el cambio. 

    cout << "se ha devuelto el cambio en " << matriz[sistemaMonetario.size()-1][cambio] << " monedas:"<<endl<<endl;
    int dinero = 0, j = cambio;
    for(int i = sistemaMonetario.size() - 1; i > 0; i--){
            if(matriz[i][j] != matriz[i-1][j] && dinero < cambio){
                if(sistemaMonetario[i] > 200){
                    cout<< ((int)(j / sistemaMonetario[i])) << " billetes de " << (sistemaMonetario[i] / 100) <<" euros, ";
                }
                else if(sistemaMonetario[i] == 200 || sistemaMonetario[i] == 100){
                    cout<< ((int)(j / sistemaMonetario[i])) << " monedas de " << (sistemaMonetario[i] / 100) <<" euros, ";
                }
                else{cout<< ((int)(j / sistemaMonetario[i])) << " monedas de " << (sistemaMonetario[i]) <<" centimos, "; }

                j -= sistemaMonetario[i];
                dinero += sistemaMonetario[i];
            }
    }
    cout<<endl<<endl;
}

void mostrarTabla(vector<int> &cantidad, int cambio, vector<float> &sistemaMonetario, vector<vector<float>> &matriz){
    float inf = INFINITY;
    int dinero = 0, j = cambio;
    int imprime = 0;
    
    cout<<endl<< "         ";

    for(int i = 0; i < cambio + 1; i++){
        if(i < 10){
            cout << i << "    ";
        }
        else{
            cout << i << "   ";
        }
    }

    cout<<endl<<endl;

    //Con este bucle for se imprime de manera ordenada la matriz para visualizar y entender la solución.

    for(int i = 0; i < sistemaMonetario.size(); i++){
        if(sistemaMonetario[i] < 10){
            cout << sistemaMonetario[i] << "        ";
        }
        else if(sistemaMonetario[i] < 100){
            cout << sistemaMonetario[i] << "       ";
        }
        else if(sistemaMonetario[i] < 1000){
            cout << sistemaMonetario[i] << "      ";
        }
        else if(sistemaMonetario[i] < 10000){
            cout << sistemaMonetario[i] << "     ";
        }
        else{
            cout << sistemaMonetario[i] << "    ";
        }
        for(int j = 0; j < cambio + 1; j++){

            if(matriz[i][j] == inf){
                cout<<matriz[i][j]<< "  ";
            }
            else if(matriz[i][j] > 9){
                cout<<matriz[i][j]<< "   ";
            }
            else {cout<<matriz[i][j]<< "    ";}
        }
        cout << endl;
    }

    cout<<endl;
    cout << "se ha devuelto el cambio en " << matriz[sistemaMonetario.size()-1][cambio] << " monedas:"<<endl<<endl;

    for(int i = sistemaMonetario.size() - 1; i > 0; i--){
            if(matriz[i][j] != matriz[i-1][j] && dinero < cambio){

                /*
                Con este primer if else averiguamos qué monedas y qué cantidad de ellas se utilizan en el cambio. Hay que variar la manera 
                en que se hallan dicha información respecto al cambio con monedas ilimitadas. Tenemos dos opciones, partiendo de que una moneda se ha utilizado
                cuando varía del valor en la fila anterior en la misma columna. Si se han utilizado todas las monedas (ahí usamos el vector cantidad) entonces saltamos
                un total de cantidad[i] * sistemaMonetario[i], es decir el precio total obtenido usando cantidad[i] monedas. Si no se han utilizado todas las monedas,
                entonces se ha usado el número entero que da dividir j (el cambio total) entre el valor de la moneda.
                */

                if(cantidad[i] * sistemaMonetario[i] < j){
                    dinero += cantidad[i] * sistemaMonetario[i];
                    imprime = cantidad[i];
                }
                else{
                    dinero += (int)((j/sistemaMonetario[i]) * sistemaMonetario[i]);
                    imprime = (int)(j/sistemaMonetario[i]);
                }

                j -= sistemaMonetario[i] * imprime;
                /*
                Aquí solo filtramos los valores para ver si son billetes, monedas de euro o monedas de céntimo.
                */

                if(sistemaMonetario[i] > 200){
                    cout<< imprime << " billetes de " << (sistemaMonetario[i] / 100) <<" euros, ";
                }
                else if(sistemaMonetario[i] == 200 || sistemaMonetario[i] == 100){
                    cout<< imprime << " monedas de " << (sistemaMonetario[i] / 100) <<" euros, ";
                }
                else{cout<< imprime << " monedas de " << (sistemaMonetario[i]) <<" centimos, "; }
            }
    }
    cout<<endl<<endl<<endl;
}

void devolverCambioLimitado(vector<int> &cantidad, int cambio, vector<float> &sistemaMonetario, vector<vector<float>> &matriz){

    for(int i = 1; i < sistemaMonetario.size(); i++){
        for(int j = 1; j < (cambio + 1); j++){
            if(sistemaMonetario[i] <= j){
                if(((int)j/sistemaMonetario[i]) <=  cantidad[i]){
                    if(1 + matriz[i][j - sistemaMonetario[i]] < matriz[i-1][j]){
                        matriz[i][j] = 1 + matriz[i][j - sistemaMonetario[i]];
                    }
                    else{matriz[i][j] = matriz[i-1][j];}
                }
                else if (cantidad[i] == 0){matriz[i][j] = matriz[i-1][j];}
                
                else{matriz[i][j] = matriz[i][sistemaMonetario[i] * cantidad[i]] + matriz[i-1][j - (sistemaMonetario[i] * cantidad[i])];}
            }
            else{matriz[i][j] = matriz[i-1][j];}
        }
    }
}