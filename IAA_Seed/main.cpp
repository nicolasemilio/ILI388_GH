#include <iostream>
#include "IOProcedures.h"

using namespace std;
int Seed;


int main(int argc, char** argv) {

    unsigned int i;
    Capture_Params(argc,argv);
    srand48(Seed);

    cout << "La semilla ingresada es -->" << Seed << endl;
    cout << "Para definirla usamos srand(Seed)" << endl;


    cout << "Vamos a generar 3 números int aleatorios entre 0 y 10" << endl;
    for(i = 0; i < 3; i++){
        cout << int_rand(0,10) << endl;
    }

    cout << "Ahora, vamos a generar 3 números float aleatorios entre 0 y 10" << endl;
    for(i = 0; i < 3; i++){
        cout << float_rand(0,10) << endl;
    }


    return 0;
}