all:
	mpicc pvc-par.c -o par -Wall

test:
	./par < input

run:
	mpirun  -np ${np} -hostfile hosts par ${N}
