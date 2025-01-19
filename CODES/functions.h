#include <iostream>
#include<random>
#include <ctime>
#define max 5000
using namespace std;

float randon_float(){
    return ((float)rand() / RAND_MAX) * (10 - 1) + 1;
}
void initializ(float *matrix,int n){
    
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            matrix[i * n + j]=randon_float();
        }
    }
   
    
}
void stampa(float *matrix,int n){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cout<<matrix[i * n + j]<<" ";
        }
        cout<<endl;
    }
}
bool checkSym(float *matrix,int n){
    bool check=true;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(matrix[j * n + i]!=matrix[i * n + j]) {
                check=false;
            }
        }
      
    }
    return check;
}
void matTranspose(float *matrix,float *trans,int n){ 
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            trans[j * n + i]=matrix[i * n + j];
        }
    }
}

void matTransposeBlock(float *matrix,float *trans,int n){
    int size=n/2;


    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            trans[i*n +j]=matrix[j*n +i];
        }
    }
    for(int i=0;i<size;i++){
        for(int j=size;j<n;j++){
            trans[i*n +j]=matrix[j*n +i];
        }
    }
for(int i=size;i<n;i++){
        for(int j=0;j<size;j++){
            trans[i*n +j]=matrix[j*n +i];
        }
    }
    for(int i=size;i<n;i++){
        for(int j=size;j<n;j++){
            trans[i*n +j]=matrix[j*n +i];
        }
    }


}