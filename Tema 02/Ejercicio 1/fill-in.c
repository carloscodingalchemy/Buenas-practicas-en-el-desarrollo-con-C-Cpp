#include <stdio.h>

// Rellena el nombre de la función con algo descriptivo
void printParity(int number) {
    if (number % 2 == 0) {
        printf("El número %d es par.\n", number);
    } else {
        printf("El número %d es impar.\n", number);
    }
}


// Rellena los nombres de las variables para que sean claros
int main() {
    int userNumber;
    
    printf("Introduce un número: ");
    scanf("%d", &userNumber);
    
    // Llama a la función con un nombre más claro
    printParity(userNumber);
    
    return 0;
}
