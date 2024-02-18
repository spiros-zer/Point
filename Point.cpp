// Spyridon Zervos ©


#include <cmath>
#include <sstream>
#include <iostream>

#include "ComplexNumbers.h"

#include "CartesianCoordinates/CartesianCoordinates2D.h"
#include "PolarCoordinates/PolarCoordinates.h"

ComplexNumbers::ComplexNumbers(const double& lhs, const double& rhs, bool bIsPolar)
{
    if (bIsPolar)
    {
        PolarForm = new PolarCoordinates(lhs, rhs);
        ToCartesian();
    }
    else
    {
        Complex = new CartesianCoordinates2D(lhs, rhs);
        ToPolar();
    }
    Cstring = ToString(Size);
}

ComplexNumbers::ComplexNumbers() : ComplexNumbers(0, 0) {}

ComplexNumbers::ComplexNumbers(const CartesianCoordinates2D& InCoords) : ComplexNumbers(InCoords.GetX(), InCoords.GetY()){}

ComplexNumbers::ComplexNumbers(const PolarCoordinates& InCoords) : ComplexNumbers(InCoords.GetRadius(), InCoords.GetTheta(), true){}

ComplexNumbers ComplexNumbers::operator*(const ComplexNumbers& X) const
{
    return {Complex->GetX() * X.Complex->GetX() - Complex->GetY() * X.Complex->GetY(), 
            Complex->GetX() * X.Complex->GetY() + Complex->GetY() * X.Complex->GetX()};
}

ComplexNumbers ComplexNumbers::operator/(const double& InNum) const
{
    return {Complex->GetX() / InNum, Complex->GetY() / InNum};
}

ComplexNumbers ComplexNumbers::operator*(const double& InNum) const
{
    return {Complex->GetX() * InNum, Complex->GetY() * InNum};
}

ComplexNumbers ComplexNumbers::operator/(const ComplexNumbers& X) const
{
    return {(Complex->GetX() * X.Complex->GetX()) / (std::pow(X.Complex->GetX(), 2) + std::pow(X.Complex->GetY(), 2)),
            (Complex->GetX() * X.Complex->GetX() - Complex->GetX() * X.Complex->GetY()) / (std::pow(X.Complex->GetX(), 2) + std::pow(X.Complex->GetY(), 2))};
}

bool ComplexNumbers::operator==(const ComplexNumbers& X) const
{
    if (Complex->GetX() == X.Complex->GetX() && Complex->GetY() == X.Complex->GetY())
    {
        return true;
    }
    return false;
}

ComplexNumbers ComplexNumbers::operator+(const double& InNum) const
{
    return {Complex->GetX() + InNum, Complex->GetY()};
}

ComplexNumbers ComplexNumbers::operator+(const ComplexNumbers& X) const
{
    ComplexNumbers* Result = new ComplexNumbers(*Complex + *X.Complex);
    return {*Result};
}

ComplexNumbers ComplexNumbers::operator-(const double& InNum) const
{
    return {Complex->GetX() - InNum, Complex->GetY()};
}

ComplexNumbers ComplexNumbers::operator-(const ComplexNumbers& X) const
{
    ComplexNumbers* Result = new ComplexNumbers(*Complex - *X.Complex);
    return {*Result};
}

void ComplexNumbers::ToCartesian()
{
    Complex = new CartesianCoordinates2D(PolarForm->GetRadius() * std::cos(PolarForm->GetTheta()), PolarForm->GetRadius() * std::sin(PolarForm->GetTheta()));
}


void ComplexNumbers::ToPolar()
{
    PolarForm = new PolarCoordinates(Complex->GetModulus(), std::atan(Complex->GetY() / Complex->GetX()) * 180 / 3.1415);
}

std::string ComplexNumbers::ToString() const
{
    std::ostringstream OutputStringStream;
    OutputStringStream << Complex->GetX() << "" << (Complex->GetY() >= 0 ?  "+" : "") << Complex->GetY() << "i";
    return OutputStringStream.str();
}

char* ComplexNumbers::ToString(int& InSize, int Precision)
{
    int CommaPos{0};
    bool bIsPositive{false};
    
    for (int i = 0; i < Complex->GetCstringSize(); i++)
    {
        if (Complex->GetCstring()[i] == ',')
        {
            CommaPos = i;
            if (Complex->GetCstring()[i+1] != '-')
                bIsPositive = true;
            break;
        }
    }
    
    InSize = Complex->GetCstringSize() - /*parenthesis*/ 2 - /*comma*/ 1 + /*i*/ 1 + (bIsPositive ? 1 : 0);
    char* Result = new char[InSize];

    int j{1};
    for (int i = 0; i < InSize; i++)
    {
        if (j == CommaPos)
        {
            j++;
            if (bIsPositive)
            {
                Result[i++] = '+';
            }
            else
            {
                j++;
                Result[i++] = '-';
            }
            Result[i] = 'i';
        }
        else
        {
            if (Complex->GetCstring()[j] == ')')
                j++;
            Result[i] = Complex->GetCstring()[j++];
        }
    }
    return Result;
}

void ComplexNumbers::Print() const
{
    for (int i = 0; i < Size; ++i)
    {
        std::cout << Cstring[i];
    }
}
