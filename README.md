# parallel-matrix-02-noshin-tilley-taraska
parallel-matrix-bmo created by GitHub Classroom
SIMD- Single Instruction, multiple data 

Class of parallel computers that perform the same operation on multiple data points simultaneously. 
Simultaneous computations, but only a single instruction at a given moment. 
Each instruction performs same operation on multiple streams of data simultaneously

 


OpenMP- Open Multi-Processing, symmetric multiprocessing 
API that supports multi-platform shared memory multiprocessing programming. 
Way to program on shared memory devices. Parallelism occurs where every parallel thread has access to all your data. Takes advantage of parallelism by rewriting the program. 
Computation among threads. 
Three types of API requirements: compiler directives, runtime/library runtimes, environment variables. 
OpenMP types of parallelism:
-Thread Based Parallelism
-Explicit Parallelism
-Fork-Join model
-Data Scoping
-Dynamic Threads
-I/O 





MPI-Message Passing Interface 
Standardized, portable message-passing standard that functions on wide variety of parallel computing architectures. 
Way to program on distributed memory devices.
Each computer is separate and contains separate data. 
Computations among nodes. 
Uses clusters which are independent computers that are linked together by a high speed network. 



OpenMP parallelizes a program incrementally, it uses shared memory to perform intensive work on each node. MPI utilizes communication and data sharing between each node.
MPI is more like a library. 
