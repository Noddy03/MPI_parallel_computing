#include <iostream>
#include<random>
#include <ctime>
#include <mpi.h>
#include "functions.h"
#define repetitions 10
using namespace std;
void matTransposeOMP(float *matrix,float *trans,int n);
int main(int argc, char** argv) {
  cout<<"Point to Point Non Buffered Blocking"<<endl;
    int myrank,size;
    int n;
    bool check=false;
    double time;
    double start,end;
    
    n=pow(2,atoi(argv[1]));
    int rows=n,collums=n;
    cout<<"number is "<<n<<endl;
   float *matrix= new float[rows * rows];
float *transpose= new float[rows * rows];
vector<float> buffer3(n);
 initializ(matrix,n);


MPI_Init(&argc, &argv);
MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
MPI_Status stat;
MPI_Datatype rowtype;
MPI_Datatype Columntype;
MPI_Request request_send, request_recv,request_send2, request_recv2;

//MPI_Type_contiguous(rows,MPI_FLOAT, &rowtype);
  //  MPI_Type_commit(&rowtype);
   //   MPI_Type_contiguous(collums, MPI_FLOAT, &Columntype);
   // MPI_Type_commit(&Columntype);

    

bool istrue=false;
for(int i=0;i<repetitions;i++){
  MPI_Barrier(MPI_COMM_WORLD);
    start=MPI_Wtime();

  for(int i=0;i<n;i++){      
             if(myrank==0){    
            MPI_Ssend(&matrix[i*n],n,MPI_FLOAT,1,1,MPI_COMM_WORLD);
            }     
    }
      
    for(int i=0;i<n;i++){
            if(myrank==1){
                MPI_Recv(&buffer3[0],n,MPI_FLOAT,0,1,MPI_COMM_WORLD,&stat);            
           for(int j=0;j<n;j++) {
            transpose[j * n +i]=buffer3[j]; 
           }  
            }
    } 
    MPI_Barrier(MPI_COMM_WORLD);
    end=MPI_Wtime();
time+=end-start;

//MPI_Barrier(MPI_COMM_WORLD);

}
MPI_Barrier(MPI_COMM_WORLD);
time=time/repetitions;
cout<<"final time "<<time<<endl;
for(int i=0;i<n;i++){      
             if(myrank==0){    
            MPI_Ssend(&matrix[i*n],n,MPI_FLOAT,1,1,MPI_COMM_WORLD);
            }     
    }
      
    for(int i=0;i<n;i++){
            if(myrank==1){
                MPI_Recv(&buffer3[0],n,MPI_FLOAT,0,1,MPI_COMM_WORLD,&stat);            
           for(int j=0;j<n;j++) {
            if(transpose[i * n +j]==buffer3[j]) check=true ;
            check=false; 
           }  
            }
    }    
    if(myrank==0){
  if(check==true) cout<<"The matrix is symmetric"<<endl;
  cout<<"The matrix is not symmetric"<<endl;
}
 cout<<"deallocation"<<endl;
delete[] matrix;
delete[] transpose;


MPI_Finalize();
    return 0;
}


