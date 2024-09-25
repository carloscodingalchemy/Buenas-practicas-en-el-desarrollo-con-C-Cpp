#include <stdio.h>

/**
 * @brief 
 * 
 * @param a 
 * @param b 
 * @return int 
 */
int suma(int a, int b) {
    return a + b;
}

int main() {
    int resultado = suma(5, 3);
    
    printf("El resultado es: %d\n", resultado);
    
    return 0;
}
