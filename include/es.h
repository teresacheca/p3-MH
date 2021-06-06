#include <iostream>
#include <fstream>
#include <vector>
#include "../include/random.h"
#include <stdlib.h>
#include <algorithm>
#include <math.h>



#ifndef ENFRIAMIENTO_SIMULADO_H
#define ENFRIAMIENTO_SIMULADO_H

using namespace std;



class ES{
    public:
        int n, m;

        int evaluaciones = 100000;

        double M, max_vecinos, max_exitos;

        int num_vecinos=0, num_exitos=0, contador_evaluaciones=0;

        double T, beta , T_fin = pow(10, -3) ;

        double mu = 0.3, fi=0.3;

        double mejor_coste;
        std::vector<int> mejor_solucion;

        double coste_actual;

        std::vector<int> sel;
        std::vector<int> vecinos;

        std::vector<std::vector<float>> matriz_distancias;

        ES(string f);

        ES();

        void leer_matriz(string f);

        double funcion_objetivo(std::vector<int> v);

        double funcion_principal();

        void generar_solucion_inicial();

        void generar_temperatura_inicial();

        //El primer elemento de la pareja es el vecino y el segundo el índice en el que se encuentra
        pair<int,int> genera_vecino();

        double factorizar(int anterior, int nuevo, std::vector<int> v, double coste);

        bool criterio_metropolis(double incremento);

        double enfriamiento_Cauchy(double tem);

        void setSel(vector<int> v);

        void setMatriz(vector<std::vector<float>> matriz, int _n, int _m);

        void init();

        vector<int> getSel();

        void limpiar();

        void generar_vecinos();
};

#endif