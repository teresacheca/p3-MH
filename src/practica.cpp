#include <iostream>
#include "../include/es.h"
//#include "../include/BL.h"
#include <fstream>
#include <vector>
//#include "../include/random.h"
#include <stdlib.h>
#include <algorithm>
#include "../include/timer.h"
#include "../include/bmb.h"
#include "../include/ils.h"
#include "../include/ils_es.h"

float calcula_desviacion(float mejor, float obtenido){
  float desviacion;

  desviacion = abs(100*(mejor-obtenido)/mejor);

  return desviacion;

}


int main(int argc, char *argv[]){

  if (argc <= 1) {
		cerr<<"\nEl programa necesita un fichero y un float como parametro\n\n";
		return 0;
	}

  double valor;
  double time;
  float desviacion;

  float mejor_coste = (float)strtod(argv[2],NULL);

  start_timers();

  cout << endl;
  cout << "DATOS: " << argv[1] << endl;
  cout << endl;

  cout << "----------------------ENFRIAMIENTO SIMULADO----------------------" << endl;
  start_timers();
  ES enfriamientoSimulado(argv[1]);
  valor =enfriamientoSimulado.funcion_principal();
  time= elapsed_time();
  desviacion = calcula_desviacion(mejor_coste, valor);
  cout << "Tiempo: " << time << " seg"<< endl;
  cout << "Desviacion: " << desviacion << endl; 

 cout << "---------------------BÚSQUEDA MULTIARRANGUE BÁSICA--------------------- "<< endl;
  BMB bmb(argv[1]);
  valor =bmb.funcion_principal();
  time= elapsed_time();
  desviacion = calcula_desviacion(mejor_coste, valor);
  cout << "Tiempo: " << time << " seg"<< endl;
  cout << "Desviacion: " << desviacion << endl;

 cout << "----------------------BÚSQUEDA LOCAL REITERADA----------------------" << endl;
  ILS ils(argv[1]);
  valor =ils.funcion_principal();
  time= elapsed_time();
  desviacion = calcula_desviacion(mejor_coste, valor);
  cout << "Tiempo: " << time << " seg"<< endl;
  cout << "Desviacion: " << desviacion << endl;

 cout << "----------------------HÍBRIDO ILS-ES----------------------" << endl;
  ILS_ES ils_es(argv[1]);
  valor =ils_es.funcion_principal();
  time= elapsed_time();
  desviacion = calcula_desviacion(mejor_coste, valor);
  cout << "Tiempo: " << time << " seg"<< endl;
  cout << "Desviacion: " << desviacion << endl;
  
}