#include <iostream>
#include "../include/greedy.h"
#include <fstream>
#include <vector>
#include "../include/random.h"
#include <stdlib.h>
#include <algorithm>


//#include "timer/timer.h"



#ifndef BL_H
#define BL_H

using namespace std;

struct puntos
    {
        int indice;
        double contribucion = 0;
    };

class BL{
    public:
        //Elementos seleccionados ordenados con greedy
        std::vector<puntos> sel;

        //Guardamos los vecinos ya explorados y descartados
        std::vector<puntos> explorados;

        std::vector<puntos> vecinos;

        std::vector<std::vector<float>> matriz_distancias;
        
        unsigned long semilla;

        int evaluaciones =100000;
            
        //n=nº elementos totales; m=nº muestra
        int n, m;

        string fichero;

        BL( string f);

        BL();

        double funcion_principal();

        void leer_matriz(string f);

        void generar_seleccionados();

        void factorizar(int anterior, int nuevo);

        double funcion_objetivo(vector<puntos> v);

        vector<puntos> ordenar_por_contribucion(vector<puntos> v);

        double obtener_contribucion_elemento(int e, vector<puntos> v);

        puntos genera_vecino(vector<puntos> v1, vector<puntos> v2);

        void generar_contribuciones();

        void setEvaluaciones(int eval);

        void limpiar();

        void init();

        void setMatriz(std::vector<std::vector<float>> matriz);

        void setN(int _N);

        void setM(int _M);

        vector<puntos> getSel();

        void setSel(vector<puntos> s);

        vector<puntos> getVecinos();
};

#endif