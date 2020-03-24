ECHO OFF

for ((i=1; i<=10; i++))
do
    mpiexec -f ~/hosts -n 4 ./mmult_mpi "$i"
done


