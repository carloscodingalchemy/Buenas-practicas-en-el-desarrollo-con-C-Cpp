// src/maths.cpp
#include "maths.h"

// Implementación de la función suma
int sum(int a, int b) {
    return a + b;
}

// Implementación de la función resta
int subtract(int a, int b) {
    return a - b;
}

// Implementación de la función multiplicación
int multiply(int a, int b) {
    return a * b;
}

// Implementación de la función división (con control de división por cero)
int divide(int a, int b) {
    if (b == 0) {
        throw std::invalid_argument("Division by zero is undefined.");
    }
    return a / b;
}
