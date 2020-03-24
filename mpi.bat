ECHO OFF

for ((i=100; i<=1000; i+100))
do
    mpiexec -f ~/hosts -n 4 ./mmult_mpi "$i"
done


