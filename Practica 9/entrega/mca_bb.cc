//Manuel Alberola Torres 74017527P
#include <iostream>
#include <string.h>
#include <fstream>
#include <math.h>
#include <vector>
#include <algorithm>      // std::sort
#include <queue>          // std::priority_queue
#include <chrono>

using namespace std;
using namespace chrono;

//Declaración de tipos de datos
typedef vector< vector<double> >Matrix;

struct Node {
 vector<int> emplacements;
 unsigned k;
 unsigned g; //Gasolineras asignadas
 double value;
 double optimistic;
};

struct is_worse {
  bool operator() (const Node& a, const Node& b) {
    return a.g < b.g;
  }
};

priority_queue<Node, vector<Node>, is_worse > NodosVivos;


//Declaración de funciones
bool readFile(string fileName);
bool arguments (int argc, char *argv[]);
void printVectors();
double greedy();
void setSolution(vector<int>&x);
void BranchAndBound();
bool feasible(Node nodo);
bool possible(Node nodo);
double optimistic (Node nodo);
bool orderDesc (int i,int j) { return (i>j); } //Ordena de mayor a menor


//Declaración de variables globales
int n = 0; //ciudades
int g = 0; //gasolineras
double BEST = 999999999;
int Iterations = 1;
int nodos = 0;
vector<int> V; //Numero de coches por ciudad
vector<int> V_aux; //Numero de coches por ciudad ordenados de mayor a menor
vector<int> Index; //Indices del vector original
vector<int> S; //Solution
vector<int> salida;
vector<int> T; //Ciudades sin gasolinera
Matrix matrix;
vector<int> Emplacements; //Ciudades sin gasolinera

bool orderIndex (int i,int j) { return (V[i]>V[j]); } //Ordena de mayor a menor los índices


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

      BEST = greedy();

      //First node
      Node node;
      node.k=0;
      node.g=0;
      node.value=0;
      node.optimistic=999999999;
      node.emplacements = vector<int> (n, 0);
      //Add first node
      NodosVivos.push(node);
      nodos++;
      auto begin = high_resolution_clock::now();

      //Start algorithm
      BranchAndBound();

      auto end = high_resolution_clock::now();
      double totalTime = duration_cast<milliseconds>(end-begin).count();
      cout<<"Bb: " <<BEST <<endl;
      cout<<"Emplacements: ";
      for(int i = 0; i<Emplacements.size(); i++){
        if(Emplacements[i] == 1){
          cout<<i <<" ";
        }
      }

      cout<<endl <<"CPU time (ms): " <<totalTime <<endl;
      cout<<"Iterations of loop while: " <<Iterations <<endl;
    }
    return 0;
}


void BranchAndBound(){
  Node expandir;

  while(!NodosVivos.empty()){
    do{
      Iterations ++;
      expandir = NodosVivos.top(); //Asign first node
      NodosVivos.pop(); //Extract first node
    }while (expandir.value>= BEST && !NodosVivos.empty());

    if(expandir.k < n){
      //Expand tree
      Node hijo1 = expandir;
      Node hijo2 = expandir;

      //hijo1.emplacements[expandir.k] = 0;
      hijo2.emplacements[expandir.k] = 1;

      hijo1.k = expandir.k + 1;
      hijo2.k = expandir.k + 1;

      //hijo1.g = expandir.g + 0;
      hijo2.g = expandir.g + 1;

      if(possible(hijo1)){
        hijo1.optimistic = optimistic(hijo1);

        if(hijo1.k == n && hijo1.g == g){ //nodo hoja && todas las gasolineras posibles asignadas
            setSolution(hijo1.emplacements);
            hijo1.value = greedy();
            if(hijo1.value <= BEST){
              BEST = hijo1.value;
              Emplacements = hijo1.emplacements;
            }
        }
        if(hijo1.optimistic < BEST){
          NodosVivos.push(hijo1);
        }
      }

      if(possible(hijo2)){
        hijo2.optimistic = optimistic(hijo2);

        if(hijo2.k == n && hijo2.g == g){ //nodo hoja && todas las gasolineras posibles asignadas
            setSolution(hijo2.emplacements);
            hijo2.value = greedy();
            if(hijo2.value <= BEST){
              BEST = hijo2.value;
              Emplacements = hijo2.emplacements;
            }
        }
        if(hijo2.optimistic < BEST){
          NodosVivos.push(hijo2);
        }
      }
    }
  }
}

bool feasible(Node nodo){
  if(nodo.g <= g){
    return true;
  }else{
    return false;
  }
}

/*
* Cota optimista empleada para poda
* Devuelve el mejor valor que se puede conseguir. Puede ser imposible.
* Si el mejor valor que se puede conseguir es peor que el mejor que
* tenemos hasta el momento se poda el nodo.
*/
double optimistic(Node nodo){

  for(int i = nodo.k; i< nodo.emplacements.size(); i++){
    nodo.emplacements[i] = 1;
  }

  setSolution(nodo.emplacements);
  nodo.optimistic = greedy();
  return nodo.optimistic;
}

/*
*Check if the combination is possible
*/
bool possible(Node nodo){ if (nodo.g > g){ return false; }else{ return true; }}

void setSolution(vector<int>&x){
  S.clear();
  T.clear();

  for(int i=0; i<x.size(); i++){
    if(x[i] == 1){
      S.push_back(i);
    }else{
      T.push_back(i);
    }
  }
}

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
* Empleada para pruebas
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
