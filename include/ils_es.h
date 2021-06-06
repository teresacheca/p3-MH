#include <iostream>
#include "../include/BL.h"
#include <fstream>
#include <vector>
#include "../include/random.h"
#include <stdlib.h>
#include <algorithm>
#include "../include/es.h"




#ifndef ILS_ES_H
#define ILS_ES_H

using namespace std;



class ILS_ES{
    public:
       
        int iteraciones = 10;

        std::vector<std::vector<float>> matriz_distancias;

        std::vector<int> sel;

        std::vector<int> mejor;

        double mejor_valor;

        int n, m;
            
        string fichero;

        ES es;

        ILS_ES( string f);

        double funcion_principal();

        void leer_matriz(string f);

        void actualizar(std::vector<int> v);

        vector<int> modificar(vector<int> v);

        vector<int> criterioAceptacion(vector<int> v1, vector<int> v2, vector<int> v3);

        vector<int> getIndices(vector<int> v);

        void generar_seleccionados();
};

#endif