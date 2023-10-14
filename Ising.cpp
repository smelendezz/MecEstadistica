//Inclusión librerías
#include <iostream> 
#include <cstdlib>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <fstream>

int rand_gen(); // Función para generar números aleatorios 0 o 1

double rand_double(); // Función para generar números aleatorios entre 0 y 1 con diferente semilla

int energia(int arreglo[], int t, int dim);// Función que calcula la energía del sistema

int magnetizacion(int arreglo[], int t);// Función que calcula la  magnetización

//NOTA:Se implementan las funciones despues de la función main

int main() {

    //  
    int dim_red = 10; //Dimensión de la cuadricula
    int N = dim_red*dim_red; //Numero de espínes
    int array [N] {0}; //Se crea el arreglo donde se guardara el     estado de cada espín de la red
    int a =0; //Numero aleatorio entre 0 y 19 para seleccionar una posición al zar de la red 
    double b=0.0; //Guarda un numero aleatorio entre o y 1.
    double en; //energia
    double mag; //magnetización
    double en_temp=0; //variable que guarda una energía temporal
    double del_en =0; //Cambio de energía
    double Tr=0.0;// T/Tc
    double p=0; //Variable que guarda un numero entre 0 y 1 con probabilidad uniforme
    double prom_e=0.0; //Energía Promedio 
    double prom_M=0.0; // Magnetización promedio
    int pasos_met=10000;  
    int temperaturas=200; 

  srand(time(0)); // Se inicia la semilla de numero aleatorios diferentes para cada compilación
  
  

  
    //Escogencia espín
    //std::cout<< energia(array, N, dim_red)<<std::endl; Valor energía
    std::ofstream fout("output_dataEnergy.txt");
    fout << "Iteracion" << "  "<< "Energia" <<std::endl;

    //Algoritmo de Metrópolis
    
    for(int jj = 1; jj < temperaturas; ++jj) {
      
    Tr=0.01;
    //Se llena el arreglo con espines aleatorios:
    for(int ii = 0; ii < N; ++ii) {
       array[ii]=rand_gen();
    }
      
      for(int ii = 0; ii < pasos_met; ++ii) {
      a = rand() % N;
      en=energia(array, N, dim_red);
        if(array[a] == -1){
          array[a]=1;
          }
          else{
          array[a]=-1;
        }
      en_temp=energia(array, N, dim_red);
      del_en=en_temp-en;
      if (del_en>0)  {
        p= ((double)rand()) / RAND_MAX;
        if (p<=std::exp(-0.440685/Tr))
          {
          //continue;
            array[a]=array[a];
          }
          else{
          array[a]=array[a]*-1;
          }
        }
        mag=magnetizacion(array, N);
        en=energia(array, N, dim_red);
      // Imprime el valor de la energía
      //Calculo de la energía promedio a partir del paso 500
      if(ii>=pasos_met/2){
        prom_e=prom_e+en;
        prom_M=prom_M+mag;
      }
      //fout<<ii<<"  "<<en<<std::endl;
      }
      prom_e=2*prom_e/pasos_met;
      prom_M=2*prom_M/pasos_met;
      
    fout<<jj<<"  "<<prom_e<<"  "<<prom_M/N<<std::endl;
    }

    
    fout.close();
  for(int ii = 0; ii < dim_red; ++ii) { 
    for(int jj = 0; jj < dim_red; ++jj) {
     std::cout<< array[(dim_red)*ii+jj]; 
  }
  std::cout<<std::endl;
  }
    return 0;
    }



int rand_gen() // Implementación de la función generadora de numero aleatorio 0 o 1
{
  double N=0;

  N= ((double)rand()) / RAND_MAX;
  if (N<0.5){
    return -1;
  } 
  else{
    return 1;
  }
}


int energia(int arreglo[], int t, int dim)
{
  int E=0;
  int Eh=0;
  int Ev=0;
  for(int ii = 0; ii < dim; ++ii) { 
      for(int jj = 0; jj < dim-1; ++jj) {
        Eh=Eh+(arreglo[(dim*ii)+jj]*arreglo[(dim*ii)+(jj+1)]);
    }
  }

  for(int ii = 0; ii < dim-1; ++ii) { 
      for(int jj = 0; jj < dim; ++jj) {
        Ev=Ev+(arreglo[(dim*ii)+jj]*arreglo[((dim*(ii+1)))+jj]); 
    }
    }
  E=Eh+Ev;
  return -E;

}

int magnetizacion(int arreglo[], int t)
{
  int M = 0;
  for (int ii= 0; ii < t; ++ii) {
    M=M+arreglo[ii];
  }
  return M;
}
