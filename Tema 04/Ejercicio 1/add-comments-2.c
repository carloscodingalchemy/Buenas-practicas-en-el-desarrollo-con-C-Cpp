#include <stdio.h>


int factorial(int n) {
    if (n == 0) {
        return 1;  /** El factorial de 0 es 1, caso base */ 
    } else {
        return n * factorial(n - 1);  /** Llamada recursiva para calcular factorial */ 
    }
}


int main() {
    int numero = 5;
    int resultado = factorial(numero);

    printf("El factorial de %d es: %d\n", numero, resultado);
    
    return 0;
}
