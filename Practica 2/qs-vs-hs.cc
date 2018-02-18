//Manuel Alberola Torres 74017527P
// ANÁLISIS Y DISEÑO DE ALGORITMOS. 2017/18
// Práctica 2 de Laboratorio: Comparación empírica de la complejidad temporal de los algoritmos de ordenación de vectores Quicksort y Heapsort.
// Se deben comparar en tres supuestos distintos: (1) vectores con contenido aleatorio y sin orden pre-establecido; (2) vectores ordenados; (3) vectores ordenados al contrario.
// La comparación debe hacerse mediante la "cuenta de pasos de programa"
// Consulta en el enunciado los detalles para realizar esta práctica.

#include <unistd.h>
#include <iostream>
#include <math.h>
#include <chrono>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;
using namespace chrono;

size_t pasos;

//--------------------------------------------------------------
// Middle Quick Sort
void
middle_QuickSort(int * v, long left, long right){
long i,j;
int pivot;
	if (left<right){
		i=left; j=right;
		pivot=v[(i+j)/2];
		pasos++;
		do{
			while (v[i]<pivot){
				 i++;
				 pasos++;
			}
			while (v[j]>pivot){
				 j--;
				 pasos++;
			}
			if (i<=j){
				swap(v[i], v[j]);
				i++; j--;
				pasos++;
			}
		}while (i<=j);
		if (left < j)  middle_QuickSort(v,left,j);
		if (i < right) middle_QuickSort(v,i,right);
	}
}

//--------------------------------------------------------------
//HEAPSORT
// Procedure sink used by Heapsort algorith
// Sink an element (indexed by i) in a tree to keep the heap property. n is the size of the heap.

void sink(int *v, size_t n, size_t i)
{
size_t largest;
size_t l, r; //left and right child

do{
		pasos++;
   	largest = i;  // Initialize largest as root
    l = 2*i + 1;  // In a heap, left child (if exists) of node i is at (2*i + 1) position
    r = 2*i + 2;  // right child (if exists) of node i is at (2*i + 2) position

    // If left child exists and left child is larger than root
    if (l < n && v[l] > v[largest]) //Note that l>=n means that  root (or largest) node has not left child
        largest = l;

    // If right child exists and right child is larger than largest so far
    if (r < n && v[r] > v[largest])
        largest = r;

    // If largest is still root the process is done
    if (largest == i) break;

	// If not (largest has changed), swap new largest with current node i and repeat the process with childs.
    swap(v[i], v[largest]);
 	i=largest;
   } while (true);
}

//--------------------------------------------------------------
// Heapsort algorithm
void heapSort(int *v, size_t n)
{
    // Build heap with the input array
    for (size_t i = n / 2 - 1; i >= 0; i--){
				pasos++;
        sink(v, n, i);
		if (i==0) break; //as size_t is unsigned type
	}
	// Now we have a HEAP on the input array, let's take this to sort the array.
    // One by one extract the first element, which is the largest, swap it with the last element of the vector and rebuild heap by sinking the new placed element on the begin of vector.
    for (size_t i=n-1; i>0; i--)
    {
        // Move current root to the end.
				pasos++;
        swap(v[0], v[i]);
 		//Now largest element is at the end but do not know if the first element is well placed, so sink process is required
        sink(v, i, 0);
    }
}

int main(void){

	int * v;
	int * w;
	int * m;

  int iteraciones = 30;
	size_t size;
	srand(getpid());

	cout<<"QUICKSORT VERSUS HEAPSORT."
	<<endl
	<<"Average processing Msteps (millions of program steps)"
	<<endl
	<<"Number of samples (arrays of integer): " <<iteraciones
	<<endl
	<<endl;

	cout<< "\t" <<"RANDOM ARRAYS"<< "\t\t"<< "SORTED ARRAYS"<< "\t\t"<<"REVERSE SORTED ARRAYS" <<endl;
	cout<< "\t" <<"-------------------"<< "\t"<< "-------------------"<< "\t"<<"-------------------" <<endl;

	cout<<"Size	QuickSort HeapSort	QuickSort HeapSort	QuickSort HeapSort" <<endl;
	cout<<"============================================================================" <<endl;

	for (int exp = 15; exp <= 23; exp++){
		size = (size_t) powl(2,exp);
		v = new int [size]; //Random vector
		w = new int [size];	//Sorted vetor
		m = new int [size]; //Reverse Sorted vector

		//Fill vectors
		for (size_t j = 0; j < size; j++){ //Push random numbers
			v[j] = rand();
			w[j] = j;
			m[j] = size-j;
		}

		if (v){
			cout << size << "\t" << std::flush;
      auto resultadoQuick = 0.0;
			auto resultadoHeap =  0.0;

			//Random
      for (int k = 0; k<iteraciones; k++){ //To make sure of the average
				for (size_t j = 0; j < size; j++){ //Push random numbers
  				v[j] = rand();
        }

				//Call to QuickSort
				pasos = 0;
  			middle_QuickSort(v, 0, size-1);
  			resultadoQuick += pasos;

				//Call to HeapSort
				pasos = 0;
				heapSort(v,size);
  			resultadoHeap += pasos;
      }
			//Write results
 			cout<< std::fixed<< setprecision(3)<< setw(8)<< (resultadoQuick / iteraciones) /1000000 << "\t" << std::flush;
			cout<< std::fixed<< setprecision(3)<< setw(8)<< (resultadoHeap / iteraciones) /1000000 << "\t" << std::flush;

			//Reestart results
			resultadoQuick = 0.0;
			resultadoHeap =  0.0;

		//Sorted
			//Call to QuickSort
    	pasos = 0;
			middle_QuickSort(w, 0, size-1);
			resultadoQuick += pasos;

			//Call to HeapSort
			pasos = 0;
			heapSort(w,size);
			resultadoHeap += pasos;

			//Write results
			cout<< std::fixed<< setprecision(3)<< setw(8)<< resultadoQuick /1000000 << "\t" << std::flush;
			cout<< std::fixed<< setprecision(3)<< setw(8)<< resultadoHeap  /1000000 << "\t" << std::flush;

			//Reestart results
			resultadoQuick = 0.0;
			resultadoHeap =  0.0;

		//Reverse sorted
			//Call to QuickSort
			pasos = 0;
			middle_QuickSort(m, 0, size-1);
			resultadoQuick += pasos;

			//Call to HeapSort
			pasos = 0;
			heapSort(m,size);
			resultadoHeap += pasos;

			//Write results
			cout<< std::fixed<< setprecision(3)<< setw(8)<< resultadoQuick /1000000 << "\t" << std::flush;
			cout<< std::fixed<< setprecision(3)<< setw(8)<< resultadoHeap  /1000000 << endl;
			resultadoQuick = 0.0;
			resultadoHeap =  0.0;

			delete [] v;
		}	else {
			cerr << "Error, not enough memory!" << endl;
			exit (1);
		}
	}
}
