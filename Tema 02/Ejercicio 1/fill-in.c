#include <stdio.h>

// Rellena el nombre de la función con algo descriptivo
void /* nombre_funcion */(int /* valor */) {
    if (/* valor */ % 2 == 0) {
        printf("El número %d es par.\n", /* valor */);
    } else {
        printf("El número %d es impar.\n", /* valor */);
    }
}

// Rellena los nombres de las variables para que sean claros
int main() {
    int /* numero_usuario */;
    
    printf("Introduce un número: ");
    scanf("%d", &/* numero_usuario */);
    
    // Llama a la función con un nombre más claro
    /* nombre_funcion */(/* numero_usuario */);
    
    return 0;
}
