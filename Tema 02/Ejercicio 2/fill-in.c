#include <stdio.h>

// Rellena el nombre de la función con consistencia para el concepto "encontrar"
int findValueIndex(int arr[], int size, int targetValue) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == targetValue) {
            return i; // Devuelve el índice si encuentra el valor
        }
    }
    return -1; // Devuelve -1 si no encuentra el valor
}

// Rellena el nombre de la función con el mismo concepto para "encontrar"
int findMaxValue(int arr[], int size) {
    int max = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

int main() {
    int numeros[] = {4, 2, 7, 1, 9, 3};
    int size = sizeof(numeros) / sizeof(numeros[0]);

    int valor = 7;
    
    // Usar una palabra consistente en las funciones relacionadas con "encontrar"
    int indice = /* nombre_funcion_1 */(numeros, size, valor);
    
    if (indice != -1) {
        printf("El valor %d se encuentra en el índice %d\n", valor, indice);
    } else {
        printf("El valor %d no se encuentra en el array\n", valor);
    }

    // Llamar a la función con un nombre coherente para "encontrar" el máximo
    int maximo = /* nombre_funcion_2 */(numeros, size);
    printf("El valor máximo en el array es: %d\n", maximo);

    return 0;
}
