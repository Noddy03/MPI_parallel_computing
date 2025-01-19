#include <iostream>
#include<random>
#include <ctime>

#include <chrono>
#include "functions.h"
using namespace std;
//float matTranspose(float ma[max][max],int n);
//bool checkSym(float ma[max][max],int n);

int main(int argc, const char * argv[]) {
  cout<<"Serial"<<endl;
    bool symm;
    int n;
  cout<<argv[1]<<endl;
        n=pow(2,atoi(argv[1]));
       
         float *matrix= new float[n * n];
float *transpose= new float[n * n];
initializ(matrix, n);


 auto start_cron = chrono::high_resolution_clock::now();
    matTranspose(matrix,transpose ,n);
  auto end_cron = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end_cron - start_cron;
    cout << "Time taken by the Transposition code serial:" << elapsed.count() << " seconds" <<endl;   
     start_cron = chrono::high_resolution_clock::now();
    symm=checkSym(matrix, n);
     end_cron = chrono::high_resolution_clock::now();
    if(symm==true) cout<<"is symmetric"<<endl;
    else cout<<"is not symmetric"<<endl;
     elapsed = end_cron - start_cron;
     cout << "Time taken by the serial code symmetric check: " << elapsed.count() << " seconds" <<endl;  
       start_cron = chrono::high_resolution_clock::now(); 
  matTransposeBlock(matrix,transpose ,n);
   end_cron = chrono::high_resolution_clock::now();
     elapsed = end_cron - start_cron;
    cout << "Time taken by the Transposition code in blocks serial:" << elapsed.count() << " seconds" <<endl;   
    return 0;

}






