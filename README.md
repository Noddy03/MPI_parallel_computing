# Matrix Transposition using MPI 
This project aim is to understand the Message Passing Interface (MPI) method of parallelism; in order to optimize two different problems , the transpose and the symmetric check  of a square matrix.  Analyze the performance and compare it with the sequential code.  
# The Repository 
The repository constains all the necessary files whoose methodologies have benn described in the paper. In the CODES folder are located all the source codes files. In the RESULTS folder are located all the data and graphics whoose done for the project as stated in the paper. 
# Instructions for the reproducibility
After have uploaded the the CODES folder and the main.pbs file, it's compulsory to execude the command
```
chmod +x main.pbs
```
this will allow the file to be executed. 
After have done that execute the command
```
qsub main.pbs
```
 This will start the simulations on the short_cpuQ with 1 selected node, 64 cpus and 128 MB of memory.
All the parameters are already assigned. At the end of the simulations a text file named 
### "matrix_parallel.txt" 
will appear which will contain all the datas, to point it out the data taken and then analyzed are the firs that appear for each method for each matrix size.
The pbs script contains the necessary modules for copilig the files, module load gcc91 and module load mpich-3.2.1--gcc-9.1.0. 
All the files will be compiled before running. Inside there is a for loop which will run the files increasing the matrix size. After another for loop will compute for the weak scaling. 
