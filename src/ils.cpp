#include <iostream>
#include "../include/ils.h"
#include <fstream>

ILS::ILS(string f){

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

double ILS::funcion_principal(){

    int contador = 0;

    bl.init();
    mejor_valor = bl.funcion_principal();
    sel = bl.getSel();
    mejor = sel;

    std::vector<puntos> sel1, sel2;

    while (contador < iteraciones)
    {
        bl.limpiar();
 
        sel1 = modificar(mejor);

        bl.setSel(sel1);

        bl.funcion_principal();

        sel2 = bl.getSel();

        actualizar(sel2);
        
        sel = criterioAceptacion(sel, sel2, mejor);

        // cout << "ITERACION " << contador << endl;
        contador++;
    }

    cout << "Mejor " << mejor_valor << endl;

    return mejor_valor;
}

void ILS::leer_matriz(string f){
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

void ILS::actualizar(std::vector<puntos> v){

    double nuevo = bl.funcion_objetivo(v);

    if(nuevo > mejor_valor){
        mejor_valor = nuevo;
        mejor = v;
    }
}

vector<puntos> ILS::modificar(vector<puntos> v){

    std::vector<int> indices_modificar, indices_vecinos, indices_sel;
    double t = 0.1 * m;


     while(indices_modificar.size() < t){
        int x =  Randint(0, m-1);
        if (std::find(indices_modificar.begin(), indices_modificar.end(), x) == indices_modificar.end()){
            indices_modificar.push_back(x);
        }
    }

    for (int i = 0; i < v.size(); i++)
    {
        indices_sel.push_back(v.at(i).indice);
    }

    while (indices_vecinos.size() < t)
    {
        int x =  Randint(0, n-m-1);
        if (std::find(indices_vecinos.begin(), indices_vecinos.end(), x) == indices_vecinos.end() && (std::find(indices_sel.begin(), indices_sel.end(), x) == indices_sel.end())){
            indices_vecinos.push_back(x);
        }
    }

    for (int i = 0; i < t; i++)
    {
        v.at(indices_modificar.at(i)).indice = indices_vecinos.at(i);
    }

    bl.setSel(v);
    bl.generar_contribuciones();
    v = bl.ordenar_por_contribucion(v);

    return v;
}

vector<puntos> ILS::criterioAceptacion(vector<puntos> v1, vector<puntos> v2, vector<puntos> v3){

    double valor1 = bl.funcion_objetivo(v1);
    double valor2 = bl.funcion_objetivo(v2);
    double valor3 = bl.funcion_objetivo(v3);

    double m;
    vector<puntos> mayor;

    if(valor1 > valor2){
        m = valor1;
        mayor = v1;
    }
    else
    {
        m = valor2;
        mayor = v2;
    }

    if(valor3 > m){
        m = valor3;
        mayor = v3;
    }

    return v3;
}