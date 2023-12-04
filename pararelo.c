#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

void sieve_parallel(int n, int rank, int size) {
    int *is_prime = (int *)malloc((n + 1) * sizeof(int));

    // Inicializar array com todos os números marcados como primos
    for (int i = 2; i <= n; i++) {
        is_prime[i] = 1;
    }

    // Dividir o trabalho entre os processos
    for (int i = 2; i * i <= n; i++) {
        if (is_prime[i]) {
            for (int j = i * i; j <= n; j += i) {
                is_prime[j] = 0;
            }
        }
    }

    // Juntar os resultados
    int *global_is_prime = NULL;
    if (rank == 0) {
        global_is_prime = (int *)malloc((n + 1) * sizeof(int));
    }

    MPI_Gather(is_prime, n + 1, MPI_INT, global_is_prime, n + 1, MPI_INT, 0, MPI_COMM_WORLD);

    // Processo 0 imprime os números primos
    if (rank == 0) {
        printf("Primes up to %d:\n", n);
        for (int i = 2; i <= n; i++) {
            if (global_is_prime[i]) {
                printf("%d ", i);
            }
        }
        printf("\n");
        free(global_is_prime);
    }

    free(is_prime);
}

int main(int argc, char **argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int n = 50;
    sieve_parallel(n, rank, size);

    MPI_Finalize();
    return 0;
}
