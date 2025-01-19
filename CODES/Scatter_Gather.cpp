#include <iostream>
#include <mpi.h>
#include <vector>
#include<cmath>
#include "functions.h"
using namespace std;
#define repetitions 10

bool is_integer(float k)
    {
        if( k == (int) k) return true;
        return false;
    }



int main(int argc, char** argv) {
    cout<<"Scatter & Gather"<<endl;
    int rank, size;
    double final_time;
    double start,end,time=0;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    int n;
     n=pow(2,atoi(argv[1]));
     if(!is_integer(sqrt(size))){
        MPI_Finalize(); 
            cout<<"Impossible to run the code, not square thread number"<<endl;
            exit(1);
     }
      int sqare=(int)sqrt(size);
     if( n%sqare!=0){
            MPI_Finalize(); 
            cout<<"Impossible to run the code, the size cannot be divided by the threads number"<<endl;
            exit(1);
         }
    int rows=n,collums=n;
 float *matrix= new float[rows * rows]; 
float *transpose= new float[rows * rows]; 
    int block_size;  // Assume perfect square distribution of processes
bool check=true;
    // Initialize the matrix on the root process
   block_size=n/sqare; 
    if (rank == 0) {
  cout<<"block_size "<<block_size<<endl;
       initializ(matrix,n); 
    } 
                                      //block_size
      vector<float> local_matrix(block_size * block_size);// Local sub-matrix block
       for(int i=0;i<repetitions;i++){
       start=MPI_Wtime();
    MPI_Scatter(&matrix[0], block_size * block_size, MPI_FLOAT, 
                &local_matrix[0], block_size * block_size, MPI_FLOAT, 
                0, MPI_COMM_WORLD);  
 
    
       
    // Create a 2D local block for easier manipulation
    vector<float> local_block(block_size*block_size);
    
    for (int i = 0; i < block_size; ++i) {
        for (int j = 0; j < block_size; ++j) {
            local_block[i * block_size + j] = local_matrix[i * block_size + j];
            
        } 
    }
    
    // Gather the transposed blocks from all processes * block_size
   vector<float> transposed_matrix(n * n);
    //vector<float> transposed_matrix2(n * n);
    MPI_Gather(&local_block[0], block_size * block_size , MPI_FLOAT, 
               &transposed_matrix[0], block_size * block_size, MPI_FLOAT, 
               0, MPI_COMM_WORLD); 
      
    // Reassemble the full transposed matrix and print the result on the root process
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n;++j) { 
                 transpose[j * n + i] = transposed_matrix[i * n + j];
            }
        } 
    end=MPI_Wtime();  
      MPI_Barrier(MPI_COMM_WORLD);
      time+=end-start;
       }
       //Symmetric check 
         
if(rank==0){
    time=time/repetitions;
cout<<"final time "<<time<<endl;
       if(check==true) cout<<"The matrix is symmetric"<<endl;
       cout<<"The matrix is not symmetric"<<endl;
}
 
     MPI_Scatter(&matrix[0], block_size * block_size, MPI_FLOAT, 
                &local_matrix[0], block_size * block_size, MPI_FLOAT, 
                0, MPI_COMM_WORLD);  
 
    
       
    // Create a 2D local block for easier manipulation
    vector<float> local_block(block_size*block_size);
    
    for (int i = 0; i < block_size; ++i) {
        for (int j = 0; j < block_size; ++j) {
            local_block[i * block_size + j] = local_matrix[i * block_size + j];
            
        } 
    }
     // Gather the transposed blocks from all processes * block_size
   vector<float> transposed_matrix(n * n);
    //vector<float> transposed_matrix2(n * n);
    MPI_Gather(&local_block[0], block_size * block_size , MPI_FLOAT, 
               &transposed_matrix[0], block_size * block_size, MPI_FLOAT, 
               0, MPI_COMM_WORLD); 
      
    // Reassemble the full transposed matrix and print the result on the root process
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n;++j) { 
                if(transposed_matrix[j * n + i] == transposed_matrix[i * n + j]) check=true;
                check=false;
            }
        }
         MPI_Finalize(); 
         
if(rank==0){
if(check==true) cout<<"The matrix is symmetric"<<endl;
    cout<<"The matrix is not symmetric"<<endl;
}
delete[] matrix;
delete[] transpose;
    
    return 0;
}

