#include <iostream>
#include "../include/bmb.h"
#include <fstream>

BMB::BMB(string f){

    ifstream ifile;
    ifile.open(f);

    if(ifile.is_open() == 0){
        cout << "NO ESTA ABIERTO" << endl;
    }

    double linea;
    ifile >> linea;
    n = linea;
    ifile >> linea;
    m=linea;

    cout << "N: " << n << "   M:  " << m << endl;

    bl.setN(n);
    bl.setM(m);

    leer_matriz(f);

    bl.setMatriz(matriz_distancias);

    bl.setEvaluaciones(10000);

    mejor_valor = 0;
}

double BMB::funcion_principal(){

    int contador = 0;

    while (contador < iteraciones){
        bl.init();
        bl.funcion_principal();

        sel = bl.getSel();

        bl.limpiar();

        Actualizar(sel);

       // cout << "ITERACION " << contador << endl;
        contador++;
    }

    cout << "Mejor " << mejor_valor << endl;

    return mejor_valor;
}

void BMB::leer_matriz(string f){
    ifstream ifile(f);
    std::vector<float> aux;
    float fila, columna, distancia;
    ifile >> fila;
    ifile >> columna;

    matriz_distancias.resize(n);

    for( int i=0 ; i<n ; i++){
        matriz_distancias[i].resize(n);
    }
  
   
    while(!ifile.eof()){
        
        ifile >> fila;
        ifile >> columna;
        ifile >> distancia;
        
        matriz_distancias[fila][columna] = distancia;
        matriz_distancias[columna][fila] = distancia;
        
    }
}

void BMB::Actualizar(std::vector<puntos> v){
    double nuevo = bl.funcion_objetivo(v);

    if(nuevo > mejor_valor){
        mejor_valor = nuevo;
        mejor = v;
    }
}