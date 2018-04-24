//Manuel Alberola Torres 74017527P
#include <iostream>
#include <string.h>
#include <fstream>
#include <math.h>
#include <vector>
#include <algorithm>    // std::sort
using namespace std;

//Declaración de tipos de datos
typedef vector< vector<double> >Matrix;

//Declaración de funciones
bool readFile(string fileName);
bool arguments (int argc, char *argv[]);
void printVectors();
bool orderDesc (int i,int j) { return (i>j); } //Ordena de mayor a menor
bool orderIndex (int i,int j);
double greedy();

//Declaración de variables globales
int n = 0; //ciudades
int g = 0; //gasolineras
vector<int> V; //Numero de coches por ciudad
vector<int> V_aux; //Numero de coches por ciudad ordenados de mayor a menor
vector<int> Index; //Indices del vector original
vector<int> S; //Solution
vector<int> T; //Ciudades sin gasolinera
Matrix matrix;




int main(int argc, char *argv[]){
    if (arguments (argc, argv) ){
      V_aux = V;

      std::sort(V_aux.begin(), V_aux.end(), orderDesc);
      std::sort(Index.begin(), Index.end(), orderIndex);

      for (int i=g-1; i>=0; i--){
        S.push_back(Index[i]);
      }

      for (int i = S.size(); i<n; i++){
        T.push_back(Index[i]);
      }

      //Print solution
      cout<<"Emplacements: ";
      for(unsigned int i=0; i<S.size(); i++){
        cout<<S[i] <<" ";
      }
      cout<<endl <<"Greedy: " << greedy() <<endl;

      //printVectors();
    }
    return 0;
}

bool orderIndex (int i,int j) { return (V[i]>V[j]); } //Ordena de mayor a menor los índices


double greedy (){
  double result = 0;
  //PSEUDOCODIGO
  //Buscar las ciudades sin gasolinera
  //De las ciudades sin gasolinera buscar la distancia mínima a una ciudad con gasolinera
  //Multipiclar el numero de coches por la distancia.

  double minima = 0;
  //Recorremos las ciudades sin gasolineras
  for(unsigned int i=0; i<T.size(); i++){
    //cout<<"Las distancias de la ciudad " <<T[i] <<" a ciudades con gasolinera son: ";
    minima=99999999;
    //Recorro las ciudades con gasolinera
    for(unsigned int j=0; j<S.size(); j++){
      //cout<<matrix[T[i]][S[j]] <<" ";
      if(matrix[T[i]][S[j]] <= minima && matrix[T[i]][S[j]] != 0){
        minima = matrix[T[i]][S[j]];
      }
    }
      //cout<< "y la minima es: " <<minima <<"y el numero de coches: "<<V[T[i]] <<" Result = "<<minima * V[T[i]] <<endl;
      result += minima * V[T[i]];
  }
  return result;
}

/**
* Gestión de argumentos del programa
**/
bool arguments (int argc, char *argv[]){
    string argument = "";
    if (argc>2){
        argument = argv[1];
        if(argument.compare("-f") == 0){
            if( !readFile(argv[2])){
              return false;
            }
        }
      } else {
        cout <<"ERROR: unknown option " <<argument <<endl;
        return false;
      }
    return true;
}

/**
* Lectura de fichero de entrada
* Almacena la información en variables [n, g, V, D]
**/
bool readFile(string fileName){

  ifstream file(fileName.c_str());
    if(file.good()) {
        file >> n;
        file >> g;
        int readedVehicles = 0;
        double readedDistance = 0;


        //Guardamos vector de ciudades
        for (int i = 0; i < n; i++){
            file >> readedVehicles;
            V.push_back(readedVehicles);
        }

        //Guardamos vector de índices
        for (int i = 0; i < n; i++){
            Index.push_back(i);
        }

        Matrix memo (n, vector<double>(n, -1.0));
        matrix = memo;
        //Guardamos matriz caminos
        for (int fila = 0; fila <n; fila++){
          for (int columna = 0; columna < n; columna++){
            file >> readedDistance;
            matrix[fila][columna] = readedDistance;
          }
        }
        file.close();
    } else {
        cout <<"ERROR: can’t open file: " + fileName <<endl;
        return false;
    }
    return true;
}

/**
* Imprime el contenido de los vectores
**/
void printVectors(){
    cout<<"Vector V: ";
    for (int i = 0; i<n; i++){
        cout <<V[i] <<", ";
    }
    cout <<endl;

    cout<<"Vector V_aux: ";
    for (int i = 0; i<n; i++){
        cout <<V_aux[i] <<", ";
    }
    cout <<endl;

    cout<<"Vector Index: ";
    for (unsigned int i = 0; i<Index.size(); i++){
      cout <<Index[i] <<", ";
    }
    cout <<endl;

    cout<<"Vector S: ";
    for (unsigned int i = 0; i<S.size(); i++){
        cout <<S[i] <<", ";
    }
    cout <<endl;

    cout<<"Vector T: ";
    for (unsigned int i = 0; i<T.size(); i++){
        cout <<T[i] <<", ";
    }
    cout <<endl;

    cout<<"Matrix: " <<endl;
    for (int fila = 0; fila <n; fila++){
      for (int columna = 0; columna < n; columna++){
        cout<<matrix[fila][columna] <<" ";
      }
      cout<<endl;
    }
      cout <<endl;
}
