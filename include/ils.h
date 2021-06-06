#include <iostream>
#include "../include/BL.h"
#include <fstream>
#include <vector>
#include "../include/random.h"
#include <stdlib.h>
#include <algorithm>




#ifndef BUSQUEDA_LOCAL_REITERATIVA_H
#define BUSQUEDA_LOCAL_REITERATIVA_H

using namespace std;



class ILS{
    public:
       
        int iteraciones = 10;

        std::vector<std::vector<float>> matriz_distancias;

        std::vector<puntos> sel;

        std::vector<puntos> mejor;

        double mejor_valor;

        int n, m;
            
        string fichero;

        BL bl;

        ILS( string f);

        double funcion_principal();

        void leer_matriz(string f);

        void actualizar(std::vector<puntos> v);

        vector<puntos> modificar(vector<puntos> v);

        vector<puntos> criterioAceptacion(vector<puntos> v1, vector<puntos> v2, vector<puntos> v3);
};

#endif