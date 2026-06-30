#pragma once
#include <cmath>
#include <iostream>

class Circle {
private:
    double radius;

public:
    // Constructor
    Circle(double radius = 0.0) : radius(radius) {}

    // Getters
    double getRadius() const { return radius; }

    // Setters
    void setRadius(double radius) { this->radius = radius; }

    // Calculate area
    double area() const {
        return 3.14 * pow(radius, 2);
    }

    // Calculate circumference
    double circumference() const {
        return 2 * 3.14 * radius;
    }

    // Calculate perimeter
    double perimeter() const {
        return 2 * 3.14*radius;
    }
};