#include <stdio.h>
#include <stdlib.h>

void sieve_serial(int n) {
    int *is_prime = (int *)malloc((n + 1) * sizeof(int));

    // Inicializar array com todos os números marcados como primos
    for (int i = 2; i <= n; i++) {
        is_prime[i] = 1;
    }

    // Marcar os múltiplos como não primos
    for (int i = 2; i * i <= n; i++) {
        if (is_prime[i]) {
            for (int j = i * i; j <= n; j += i) {
                is_prime[j] = 0;
            }
        }
    }

    // Imprimir números primos
    printf("Primes up to %d:\n", n);
    for (int i = 2; i <= n; i++) {
        if (is_prime[i]) {
            printf("%d ", i);
        }
    }

    free(is_prime);
}

int main() {
    int n = 50;
    sieve_serial(n);

    return 0;
}
