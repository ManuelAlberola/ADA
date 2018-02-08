//Manuel Alberola Torres 74017527-P
/*
Análisis y Diseño de Algoritmos
PRÁCTICA 1 de laboratorio: Análisis empírico de la complejidad temporal de los algoritmos.

Objetivo de la práctica:

- Refrescar el lenguaje de programación y el uso de las herramientas: compilador, make, editor,  etc...
- Saber obtener de manera empírica la complejidad temporal de un algoritmo, generando instancias aleatorias y cronometrando el tiempo que tarda en resolverlas.
- Saber medir tiempos de proceso utilizando la librería chrono del estándar C++11.
- Conocer el tipo de datos "size_t" para representar el tamaño de los objetos, útil para evitar desbordamientos de los tipos básicos; size_t puede almacenar el máximo tamaño de cualquier objeto.
- Conocer la herramienta Gnuplot para dibujar funciones matemáticas y su comando fit para encontrar la función que mejor se ajusta a una serie de datos.
*/

#include <unistd.h>
#include <iostream>
#include <math.h>
#include <chrono>

using namespace std;
using namespace chrono;

//--------------------------------------------------------------
// Bubble sort basic algorithm

void middle_QuickSort(int * v, long left, long right){
long i,j;
int pivot,aux;
  if (left<right){
	i=left; j=right;
	pivot=v[(i+j)/2];
	do{
		while (v[i]<pivot) i++;
		while (v[j]>pivot) j--;
		if (i<=j) {
		  aux=v[i]; v[i]=v[j]; v[j]=aux;
		  i++; j--;
		}
	}while (i<=j);
	if (left<j)  middle_QuickSort(v,left,j);
	if (i<right) middle_QuickSort(v,i,right);
  }
}
//--------------------------------------------------------------


int main(void){

	int * v;
  int iteraciones = 30;
	size_t size;

	srand(getpid());

	cout << "BubbleSort CPU times in milliseconds:"
		<< endl
		<< "Size \t CPU time (ms.)"
		<< endl
		<< "----------------------------"
		<< endl;

	for (int exp = 15; exp <= 23; exp++){
		size = (size_t) powl(2,exp);
		v = new int [size];
		if (v){
			cout << size << "\t\t" << std::flush;

      auto resultado = 0.0;

      for (int k = 0; k<iteraciones; k++){
        for (size_t j = 0; j < size; j++){
  				v[j] = rand();
        }

      	auto begin = high_resolution_clock::now();
  			middle_QuickSort(v, 0, size-1);
  			auto end = high_resolution_clock::now();
  			resultado += duration_cast<milliseconds>(end-begin).count();
      }
      cout <<  resultado / iteraciones <<endl;

			for (size_t i = 1; i < size; i++)
				if (v[i] < v[i-1]){
					cerr << "Panic, array not sorted! " << i << endl;
					exit(1);
				}

			delete [] v;
		}	else {
			cerr << "Error, not enough memory!" << endl;
			exit (1);
		}
	}
}
