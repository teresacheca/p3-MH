#include <iostream>
#include "../include/BL.h"
#include <fstream>
#include <vector>
#include "../include/random.h"
#include <stdlib.h>
#include <algorithm>


//#include "timer/timer.h"



#ifndef BMB_H
#define BMB_H

using namespace std;


class BMB{
    public:
       
        int iteraciones = 10;

        std::vector<std::vector<float>> matriz_distancias;

        std::vector<puntos> sel;

        std::vector<puntos> mejor;

        double mejor_valor;

        int n, m;
            
        string fichero;

        BL bl;

        BMB( string f);

        double funcion_principal();

        void leer_matriz(string f);

        void Actualizar(std::vector<puntos> v);
};

#endif