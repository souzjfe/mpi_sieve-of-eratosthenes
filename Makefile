compile:
	mpicc sieve_serial.c -o sieve_serial
	mpicc sieve_parallel.c -o sieve_parallel
clean:
	rm sieve_serial sieve_parallel
run_serial:
	mpirun -np 1 ./sieve_serial
run_parallel:
	mpirun -np 32 --host localhost,172.20.222.240 ./sieve_parallel