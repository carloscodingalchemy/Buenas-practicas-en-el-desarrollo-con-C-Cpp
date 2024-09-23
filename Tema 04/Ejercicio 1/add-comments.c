#include <stdio.h>

/**
 * @brief 
 * 
 * @param a 
 * @param b 
 * @return int 
 */
int suma(int a, int b) {
    return a + b;  /** Esta función suma dos números */ 
}

int main() {
    int resultado = suma(5, 3);  /** Almacena el resultado de la suma */ 
    
    printf("El resultado es: %d\n", resultado);  /** Imprime el resultado */ 
    
    return 0;
}
