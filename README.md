# parallel-matrix-02-noshin-tilley-taraska
parallel-matrix-bmo created by GitHub Classroom

# Distributed Parallel Computing
For our solution to work, we had to alter a number of files where certain algorithms resided. For example, the original mmult()
function and the optimized SIMD mmult() function reside in mmult.c. From this file and test_mmult.c, we were able to format the 
time it took for these functions to run and put them into the data.txt file to be later processsed into he gnu plot. The size of
these graphs and the respective time it took for each algorithm to run was generated using the writeArrayToFile() function added
to mat.c. We also altered mmult_mpi_omp.c and mmult_omp_timing.c in order to properly run OpenMP and MPI.
The different types of algorithms we used in this lab were no optimization ,SIMD, Symmetric multiproccessing, and Distributed Memory.

# Team Work
We did lock the master branch as we did in other labs. We all pretty much worked on this project at the same time so one person
would tell the others what they did and the others would review it to make sure it worked properly and didn't break other files.

## Jack Tilley
I worked on the README, generating data for the graphs and formatting that data into tabular format, I did the Trello board,
and I did the vectorized SIMD matrix multiplication. I also helped with bugs and trouble shooting problems in C.

## Sarah Noshin
I worked on answering the research question and the matrix multiplication on Wolfgand cluster with OMP and made a graph which showed that OMP is faster than matrix multiplication w/o parallelization and matrix multiplication w/ SIMD.

## Dominic Taraska

I worked on answering the research question and the matrix multiplication on Wolfgand cluster with MPI (Distributed Memory). I also made the included graph and helped with general troubleshooting. 

# Full Project Life Cycle
We used the project board as a way to realize what needed to get done, we grouped tasks into when they needed to be done and
then we talked about who would do what and when.

This project was definitely unique in how the development cycle went. Since we couldn't use any of our normal IDEs to run code
for this project, we found ourselves simply writing the code in an IDE outside of the project environment and then copy pasting
that code into the project repository and then testing to see if it worked from there. This was definitely far from ideal as when
we copy pasted code, we had no idea if there was going to be any errors or if it would even work as intended and therefore just to 
get simple code to work, it took a lot of extra effort that normally is unneccesary.

Since it was almost impossible to do any type of unit testing for this project, we basically just had to test our code as we wrote
it with print statements and things like that. We did not consider any additional measures besides the ones that we knew were
specifically asked for by the project description. We did notice that initially the code given to us wasn't 100% finished so it
took a lot of effort to figure out what code needed to go where in order to get things working.

We did not have to write code to generate matices of specific sizes as the gen_matrix() function was already written for us.

As we are writing this, it is in the plan to automate the creation of graphs, as of right now, matrices along with their specific
algorithm completion times are already automated to be sent a .txt file for further processing into a gnu plot.

I would say as of right now testing and reporting is about 50% while writing the algorithms is the other 50%. There is a lot of
work involved with getting the matrices to the right format and getting files to work together properly.

# Relevant Things To Project

![alt text](https://github.com/3296Spring2020/parallel-matrix-02-noshin-tilley-taraska/blob/master/graph-page-001.jpg?raw=true)
