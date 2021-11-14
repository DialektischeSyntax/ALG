#include "mochila.hpp"
#include "cambio.hpp"
using namespace std;

int main(){
    int opt;

    do{
        cout << "|--------------------------------------------------------------------------------|" <<endl;
        cout << "|                             MENU  DE  OPCIONES                                 |" <<endl;
        cout << "|                                                                                |" <<endl;
        cout << "|                          1: Problema del cambio.                               |" <<endl;
        cout << "|                                                                                |" <<endl;
        cout << "|                          2: Problema de la mochila.                            |" <<endl;
        cout << "|                                                                                |" <<endl;
        cout << "|                    PULSE CUALQUIER OTRA TECLA PARA SALIR                       |" <<endl;
        cout << "|________________________________________________________________________________|" <<endl;
        cout <<endl<<endl;
        cin >> opt;
        cin.ignore();

        if(opt == 1){
            cambio(opt);
        }
        else if(opt == 2){
            mochila();
        }
        else{
            return 0;
        }
    }while(opt==1 || opt==2);

}
