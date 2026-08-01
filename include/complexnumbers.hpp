#pragma once

#include <iosfwd>

class Complex
{
    double real;
    double imaginary;

    static bool tiny(double d);

public:
    Complex(double r = 0.0, double i = 0.0);
    Complex(const Complex &c);
    ~Complex() = default;

    double re() const;
    double im() const;
    bool isZero() const;
    bool isReal() const;
    double radius() const;
    double angle() const;

    const Complex &operator=(const Complex &c);

    const Complex &operator+=(const Complex &c);
    const Complex &operator+=(double c);
    Complex operator+(const Complex &c) const;
    Complex operator+(double c) const;

    const Complex &operator-=(const Complex &c);
    const Complex &operator-=(double c);
    Complex operator-(const Complex &c) const;
    Complex operator-(double c) const;

    const Complex &operator*=(const Complex &c);
    const Complex &operator*=(double c);
    Complex operator*(const Complex &c) const;
    Complex operator*(double c) const;

    const Complex &operator/=(double d);
    const Complex &operator/=(const Complex &c);
    Complex operator/(const Complex &c) const;
    Complex operator/(double c) const;
};

bool operator==(const Complex &c1, const Complex &c2);
bool operator!=(const Complex &c1, const Complex &c2);

Complex operator!(const Complex &c);
double abs2(const Complex &c);
double abs(const Complex &c);
Complex sqrt(const Complex &c);

std::ostream &operator<<(std::ostream &os, const Complex &c);