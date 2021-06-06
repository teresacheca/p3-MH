#include <iostream>
#include "../include/es.h"
#include <fstream>
#include <math.h>

ES::ES(){

}
ES::ES(string f){

    ifstream ifile;
    ifile.open(f);

    if(ifile.is_open() == 0){
        cout << "NO ESTA ABIERTO" << endl;
    }

    //Leemos la primero línea que contiene el valor de n y m, número total de genes y número de alelos con valor 1 respectivamente
    double linea;
    ifile >> linea;
    n = linea;
    ifile >> linea;
    m=linea;

    cout << "N: " << n << "   M:  " << m << endl;

    leer_matriz(f);

    max_vecinos = 10 * m;
    max_exitos = 0.1 * max_vecinos;
    M = evaluaciones/max_vecinos;

    generar_solucion_inicial();
    
}

void ES::leer_matriz(string f){

    ifstream ifile(f);
    std::vector<float> aux;
    float fila, columna, valor;
    ifile >> fila;
    ifile >> columna;

    matriz_distancias.resize(n);

    for( int i=0 ; i<n ; i++){
        matriz_distancias[i].resize(n);
    }
  
   
    while(!ifile.eof()){
        
        ifile >> fila;
        ifile >> columna;
        ifile >> valor;
        
        matriz_distancias[fila][columna] = valor;
        matriz_distancias[columna][fila] = valor;
        
    }
}

double ES::funcion_objetivo(std::vector<int> v){
    double suma=0;
    
    vector<int>::iterator it1, it2;
    it1 = it2 = v.begin();
    for(it1; it1 != v.end()-1; it1++){
        it2 = it1+1;
        for( it2; it2 != v.end(); it2++){
            suma += matriz_distancias[(*it1)][(*it2)];
 
        }
    }
    contador_evaluaciones++;

    return suma;
}

double ES::funcion_principal(){
    
    coste_actual = mejor_coste = funcion_objetivo(sel);
    mejor_solucion = sel;
    generar_temperatura_inicial();

   // cout << "T " << T <<endl; 
    bool salir = false;
    
    while(contador_evaluaciones < evaluaciones && !salir){
    //    cout << "entra" <<endl;
      // cout << "evaluacion " << contador_evaluaciones <<endl;
        do{

        //    cout << "Coste: " <<coste_actual <<endl;
            pair<int,int> nuevo = genera_vecino();

            int vecino = nuevo.first;

            num_vecinos++;
        //    cout <<"a" <<endl;
           // cout << " m: " << m <<endl;
            int indice = Randint(0, m-1);
          //  cout << "indice: " << indice <<endl; 
          //  cout << "b" <<endl;
            std::vector<int> nueva_solucion;

            int anterior = sel.at(indice);
            nueva_solucion = sel;
            nueva_solucion.at(indice) = vecino;
            double coste_nuevo = factorizar(anterior, vecino, nueva_solucion, coste_actual);
            
            double incremento_coste = coste_nuevo - coste_actual;
          //  cout << "INCREMENTO: " << incremento_coste << endl;

            if( criterio_metropolis(incremento_coste) ){
              //  cout << "ACEPTAMOS " <<endl;
                sel = nueva_solucion;
                coste_actual = coste_nuevo;

                vector<int>::iterator it;
                it = vecinos.begin() + nuevo.second;
                vecinos.erase(it);
                vecinos.push_back(anterior);

                num_exitos++;

                if(coste_actual > mejor_coste){
                    mejor_coste = coste_actual;
                    mejor_solucion = sel;
                }
            }

       
        }while( num_vecinos < max_vecinos && num_exitos < max_exitos);
       // }while( num_vecinos < 3);

        if(num_exitos == 0){
            salir = true;
        }else{
            num_exitos = 0;
            num_vecinos = 0;
            
            T = enfriamiento_Cauchy(T);
        }
    }

   // cout << "Mejor coste " << mejor_coste <<endl;
    return mejor_coste;
}


void ES::generar_solucion_inicial(){
    Set_random(10);
    int x;
    while(sel.size() < m){
        x = Randint(0, n);
        if(std::find(sel.begin(), sel.end(), x) == sel.end()) {
            sel.push_back(x);
        } 
    }

    for(int i=0; i<n; i++){
        if(std::find(sel.begin(), sel.end(), i) == sel.end()) {
            vecinos.push_back(i);
        } 
        
    }

    std::random_shuffle(vecinos.begin(), vecinos.end());

}

void ES::generar_temperatura_inicial(){
    T = (mu*mejor_coste)/(-log(fi));
    beta = (T - T_fin) /(M* T * T_fin);
    //cout <<"Beta " << beta <<endl;
}

pair<int,int> ES::genera_vecino(){

    int indice = Randint(0, vecinos.size() - 1);
    int vecino = vecinos.at(indice);

    pair<int,int> sol;
    sol.first = vecino;
    sol.second = indice;

    return sol;
}

double ES::factorizar(int anterior, int nuevo, std::vector<int> v, double coste){
    vector<int>::iterator it;
    it = v.begin();
    for(it; it!=v.end(); it++){
        coste = coste -  matriz_distancias[anterior][(*it)] + matriz_distancias[nuevo][(*it)];
    
    }
    contador_evaluaciones++;
    return coste;

}


bool ES::criterio_metropolis(double incremento){
    bool aceptamos = false;
    if(incremento < 0 ){
        aceptamos = true;
      //  cout << "               MEJORA" <<endl;
    } else if(Randint(0, 1) < exp(-incremento/T)){
        aceptamos = true;
    }

    return aceptamos;
}

double ES::enfriamiento_Cauchy(double tem){
    double nueva_t;

    nueva_t = tem/ (1+beta*tem);

    return nueva_t;
}

void ES::setSel(vector<int> v){
    sel = v;
}

void ES::setMatriz(vector<std::vector<float>> matriz, int _n, int _m){
    n = _n;
    m = _m;
    matriz_distancias.resize(n);

    for (int i = 0; i < n; i++)
    {
        matriz_distancias[i].resize(n);
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++){
            matriz_distancias[i][j] = matriz[i][j];
        }
    }
}

void ES::init(){
    max_vecinos = 10 * m;
    max_exitos = 0.1 * max_vecinos;
    M = evaluaciones/max_vecinos;
}

vector<int> ES::getSel(){
    return sel;
}


void ES::limpiar(){
    sel.clear();
    vecinos.clear();

}

void ES::generar_vecinos(){
    vecinos.clear();
    for (int i = 0; i < n; i++)
    {
        if(std::find(sel.begin(), sel.end(), i) == sel.end()) {
            vecinos.push_back(i);
        }
    }

    std::random_shuffle(vecinos.begin(), vecinos.end());
}