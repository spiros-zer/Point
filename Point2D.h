// Spyridon Zervos ©


#pragma once

#include <string>

struct PolarCoordinates;
struct CartesianCoordinates2D;

/**
 * @brief Implements and provides the basic functionality for Complex numbers. It also 
 * implements the Polar form for the Complex.
 */
struct ComplexNumbers
{
    /** @brief Complex in the form of x+jb. The x holds the real, while the y holds the imaginary part. */
    CartesianCoordinates2D* Complex;

    /** @brief The Polar form of the Complex. */
    PolarCoordinates* PolarForm;

    /** @brief Array containing the complex number. */
    char* Cstring{};

    /** @brief Size of the array. */
    int Size{0};
 
    /**** CONSTRUCTORS/DESTRUCTORS */
    ComplexNumbers(const double& lhs, const double& rhs, bool bIsPolar = false);
    ComplexNumbers(const CartesianCoordinates2D& InCoords);
    ComplexNumbers(const PolarCoordinates& InCoords);
    ComplexNumbers();
 
    /**** OPERATOR OVERLOADING */
    bool operator==(const ComplexNumbers& X) const;
    /** @brief Addition with real num */
    ComplexNumbers operator+(const double& InNum) const;
    ComplexNumbers operator+(const ComplexNumbers& X) const;
    /** @brief Subtraction with real num */
    ComplexNumbers operator-(const double& InNum) const;
    ComplexNumbers operator-(const ComplexNumbers& X) const;
    /** @brief Multiplication with num. */
    ComplexNumbers operator*(const double& InNum) const;
    ComplexNumbers operator*(const ComplexNumbers& X) const;
    /** @brief Division with num. */
    ComplexNumbers operator/(const double& InNum) const;
    ComplexNumbers operator/(const ComplexNumbers& X) const;
    
    /** @brief Transforms polar to cartesian coordinates. */
    void ToCartesian();
    /** @brief Transforms cartesian to polar coordinates. */
    void ToPolar();

    /**** STRING OPERATIONS */
    /** @brief Converts the Complex number to a std::string.*/
    std::string ToString() const;

    char* ToString(int& InSize, int Precision = 2);
    
    void Print() const;
};
