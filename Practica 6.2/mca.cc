//Manuel Alberola Torres 74017527P
#include <iostream>
#include <string.h>
#include <fstream>
#include <math.h>
#include <vector>
using namespace std;

//Declaración de tipos de datos
typedef vector<vector<double>>Matrix;

//Declaración de funciones
bool readFile(string fileName);
bool arguments (int argc, char *argv[]);
void printVectors();
double calculate(int nAux,int centinela, vector<int> vAux, vector<double> dAux);
double mca(int nAux, int g_Aux, vector<int> vAux, vector<double> dAux);
double memoization(int nAux, int g_Aux, vector<int> vAux, vector<double> dAux);

//Declaración de variables globales
int n = 0; //ciudades
int g = 0; //gasolineras
vector<int> V; //Numero de coches por ciudad
vector<double> D; //Distancia entre ciudades
bool makeRecursive = true; //Hacer opción recursiva
bool makeMatrix = false; //Imprimir matriz
Matrix matrix;

main(int argc, char *argv[]){
    if (arguments (argc, argv) ) {
      //printVectors();
      Matrix memo (n+1, vector<double>(g+1, -1.0));
      matrix = memo;

      if (makeRecursive){
        calculate(n,0, V, D);
        cout <<"Recursive: " <<  mca(n, g, V, D) << endl;
      }

       cout << "Memorizacion: " <<memoization(n, g, V, D) << endl
       << "Iterative (table): ¿?" << endl
       << "Iterative (vector): ¿?" << endl
       << "Emplacements: ¿?" << endl
       << "Assignment: ¿?" << endl
       << "Assignment cost: ¿?" << endl;

     if (makeMatrix){
       cout << "Iterative table:" << endl
       << "¿?\n" << endl;
     }
   }

   for (int fila = 0; fila <=n; fila++){
     for (int columna = 0; columna <= g; columna++){
       cout<<matrix[fila][columna] <<" ";
     }
     cout <<endl;
   }


    return 0;
}

/**
* Gestión de argumentos del programa
**/
bool arguments (int argc, char *argv[]){
    string argument = "";
    for (int i = 1; i<argc; i++){
        argument = argv[i];
        if(argument.compare("-f") == 0){
            if( !readFile(argv[i+1])){
              return false;
            }
            i++;
        } else if (argument.compare("--ignore_recursive") == 0){
            makeRecursive = false;
        }else if(argument.compare("-t") == 0){
            makeMatrix = true;
        }else{
          cout <<"ERROR: unknown option " <<argument <<endl;
          cout<<"Usage:" <<endl;
          cout<< "mca [-t] [--ignore_recursive] -f file" <<endl;
          return false;
        }
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
        int readedVehicle = 0;

        for (int i = 0; i < n; i++){
            file >> readedVehicle;
            V.push_back(readedVehicle);
        }
        double readedDistance = 0;

        for (int j = 0; j < n; j++){
            file >> readedDistance;
            D.push_back(readedDistance);
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

    cout<<"Vector D: ";
    for (int j = 0; j<n; j++){
        cout <<D[j] <<", ";
    }
    cout<<endl;
}

double calculate(int n, int centinela, vector<int> V, vector<double> D){
    double mejor = 0;
    double total=0;
    for(int i=centinela; i<n; i++){
        for(int j=centinela; j<n; j++){
            total += fabs((D[i]- D[j])*V[j]);
        }

        if (mejor == 0){
          mejor = total;
        } else if (total < mejor){
            mejor = total;
        }
        total = 0;
    }
    return mejor;
}

double mca(int n, int g, vector<int> V, vector<double> D ){
  double mejor = 0;
  double total = 0;

  if(g == 0) { return 0; }
  else if(g == 1) { calculate(n,0,V,D); }
  else if(g <= n){
    for(int i = n-1; i>=0; i--){
      total = mca(i,g-1, V, D) + calculate(n,i,V, D);
      if (mejor == 0){ mejor = total; }
      else if(total < mejor){ mejor = total;}
    }
    return mejor;
  }
}

double memoization(int n, int g, vector<int> V, vector<double> D){
  if(matrix[n][g] == -1.0){
    double mejor = 0;
    double total = 0;

    if(g == 0) { return 0; }
    else if(g == 1) { calculate(n,0,V,D); }
    else if(g <= n) {
      for(int i = n-1; i>=0; i--){
        total = memoization(i,g-1, V, D) + calculate(n,i,V, D);
        if (mejor == 0){ mejor = total; }
        else if(total < mejor){ mejor = total;}
      }
      matrix[n][g] = mejor;
    }
  }else{
    return matrix[n][g];
  }
}
