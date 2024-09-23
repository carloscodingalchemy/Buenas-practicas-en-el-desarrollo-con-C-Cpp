#include <iostream>
#include <cmath>

double calculateCircleArea(double radius) {
    return M_PI * radius * radius;
}

void printSquareArea(double sideLength) {
    std::cout << "The area of the square is: " << sideLength * sideLength << std::endl;
}

double calculateRectanglePerimeter(double length, double width) {
    return 2 * (length + width);
}

int main() {
    double radius, sideLength, length, width;

    std::cout << "Enter radius of circle: ";
    std::cin >> radius;
    std::cout << "The area of the circle is: " << calculateCircleArea(radius) << std::endl;

    std::cout << "Enter side length of square: ";
    std::cin >> sideLength;
    printSquareArea(sideLength);

    std::cout << "Enter length and width of rectangle: ";
    std::cin >> length >> width;
    std::cout << "The perimeter of the rectangle is: " << calculateRectanglePerimeter(length, width) << std::endl;

    return 0;
}

double calculateSquarePerimeter(double sideLength) {
    return 4 * sideLength;
}

void printRectangleArea(double length, double width) {
    std::cout << "The area of the rectangle is: " << length * width << std::endl;
}
