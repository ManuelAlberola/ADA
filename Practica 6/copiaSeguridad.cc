//Manuel Alberola Torres 74017527P
#include <iostream>
#include <string.h>
#include <fstream>
#include <math.h>
#include <vector>
using namespace std;

void readFile(string fileName);
int arguments (int argc, char *argv[]);
void printVectors();
int recursive();
double centroide(int nAux,int a, vector<int> vAux, vector<double> dAux);
double mca(int nAux, int g_Aux, vector<int> vAux, vector<double> dAux);
void printSolution(int nAux, int g_Aux, vector<int> vAux, vector<double> dAux);

int n = 0; //ciudades
int g = 0; //gasolineras

vector<int> V; //Numero de coches por ciudad
vector<double> D; //Distancia entre ciudades
vector<int> C; //Camino


main(int argc, char *argv[]){
    arguments (argc, argv);
    //recursive();
    //printVectors();
    vector<int> vAux = V; //Numero de coches por ciudad
    vector<double> dAux = D; //Distancia entre ciudades
    int nAux = n;
    int g_Aux = g;

    cout<<"Vector V: ";
    for (int i = 0; i<n; i++){
        cout <<vAux[i] <<", ";
    }
    cout <<endl;

    cout<<"Vector D: ";
    for (int j = 0; j<n; j++){
        cout <<dAux[j] <<", ";
    }
    cout<<endl;
    printSolution(nAux, g_Aux, vAux, dAux);
    return 0;
}

int arguments (int argc, char *argv[]){
    string argument = "";
    for (int i = 0; i<argc; i++){
        argument = argv[i];
        if(argument.compare("-f") == 0){
            readFile(argv[i+1]);
            i++;
        }
    }
    return 0;
}

void readFile(string fileName){
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

        for (int k = 0; k < n; k++){
            C.push_back(0);
        }
        file.close();
    } else {
        cout <<"ERROR: can’t open file: " + fileName <<endl;
    }
}

int recursive(){
    for (int i = 0; i<n; i++){
        for (int j = 0; j < n; j++){
            C[i] = V[i];
        }
    }
    return 0;
}

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

    cout<<"Vector C: ";
    for (int k = 0; k<n; k++){
        cout <<D[k] <<", ";
    }
    cout <<endl;
}

void printSolution(int nAux, int g_Aux, vector<int> vAux, vector<double>  dAux){
  centroide(nAux,0, vAux, dAux);
   cout <<"Recursive: " <<  mca(nAux, g_Aux, vAux, dAux) << endl
     << "Memorizacion: ¿?" << endl
     << "Iterative (table): ¿?" << endl
     << "Iterative (vector): ¿?" << endl
     << "Emplacements: ¿?" << endl
     << "Assignment: ¿?" << endl
     << "Assignment cost: ¿?" << endl
     << "Iterative table:" << endl
     << "¿?\n" << endl;
}

double centroide(int nAux, int a, vector<int> vAux, vector<double> dAux){
    double total=0;
    double mejor = 0;
    for(int i=a; i<nAux; i++){
        for(int j=a; j<nAux; j++){
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

double mca(int nAux, int g_Aux, vector<int> vAux, vector<double> dAux ){
  double total = 0;
  double mejor = 0;

  if(g_Aux == 0) { return 0; }
  else if(g_Aux == 1) { centroide(nAux,0,vAux,dAux); }
  else if(g_Aux <= nAux){
    for(int i = nAux-1; i>=0; i--){
      total = mca(i,g_Aux-1, vAux, dAux) + centroide(nAux,i,vAux, dAux);
      if (mejor == 0){ mejor = total; }
      else if(total < mejor){ mejor = total;}
    }
    return mejor;
  }
}
