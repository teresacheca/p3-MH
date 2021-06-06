#include <iostream>
#include "../include/ils_es.h"
#include <fstream>

ILS_ES::ILS_ES(string f){


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

    leer_matriz(f);

    es.setMatriz(matriz_distancias, n, m);

    es.init();

    mejor_valor = 0;
}

double ILS_ES::funcion_principal(){

    generar_seleccionados();

    int contador = 0;

    es.setSel(sel);
    es.generar_vecinos();
    mejor_valor = es.funcion_principal();

    sel = es.getSel();
 
    mejor = sel;

    std::vector<int> sel1, sel2;

    while (contador < iteraciones)
    {
        es.limpiar();
        es.generar_vecinos();

        sel1 = modificar(mejor);

        es.setSel(sel1);

        es.funcion_principal();

        sel2 = es.getSel();

        actualizar(sel2);
        
        sel = criterioAceptacion(sel, sel2, mejor);

        // cout << "ITERACION " << contador << endl;
        contador++;
    }

    cout << "Mejor " << mejor_valor << endl;

    return mejor_valor;
}

void ILS_ES::leer_matriz(string f){
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

void ILS_ES::actualizar(std::vector<int> v){

    double nuevo = es.funcion_objetivo(v);

    if(nuevo > mejor_valor){
        mejor_valor = nuevo;
        mejor = v;
    }
}

vector<int> ILS_ES::modificar(vector<int> v){

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
        indices_sel.push_back(v.at(i));
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
        v.at(indices_modificar.at(i)) = indices_vecinos.at(i);
    }

    es.setSel(v);


    return v;
}

vector<int> ILS_ES::criterioAceptacion(vector<int> v1, vector<int> v2, vector<int> v3){

    double valor1 = es.funcion_objetivo(v1);
    double valor2 = es.funcion_objetivo(v2);
    double valor3 = es.funcion_objetivo(v3);

    double m;
    vector<int> mayor;

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


void ILS_ES::generar_seleccionados(){
    Set_random(10);
    int x;
    while(sel.size() < m){
        x = Randint(0, n);
        if(std::find(sel.begin(), sel.end(), x) == sel.end()) {
            sel.push_back(x);
        } 
    }

}
