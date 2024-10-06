// tests/testmaths.cpp
#include <gtest/gtest.h>
#include "maths.h"  // Incluir el header de las funciones matemáticas

// Test para la función sum
TEST(MathTest, SumFunction) {
    EXPECT_EQ(sum(3, 4), 7);
    EXPECT_EQ(sum(-1, -1), -2);
    EXPECT_EQ(sum(-5, 5), 0);
}

// Test para la función subtract
TEST(MathTest, SubtractFunction) {
    EXPECT_EQ(subtract(10, 4), 6);
    EXPECT_EQ(subtract(0, 5), -5);
    EXPECT_EQ(subtract(5, 5), 0);
}

// Test para la función multiply
TEST(MathTest, MultiplyFunction) {
    EXPECT_EQ(multiply(3, 4), 12);
    EXPECT_EQ(multiply(-2, 5), -10);
    EXPECT_EQ(multiply(0, 10), 0);
}

// Test para la función divide
TEST(MathTest, DivideFunction) {
    EXPECT_EQ(divide(10, 2), 5);
    EXPECT_EQ(divide(9, 3), 3);
    EXPECT_THROW(divide(1, 0), std::invalid_argument);  // Test para la división por cero
}
