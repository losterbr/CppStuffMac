#pragma once

#include <iosfwd>

class Complex
{
    double real;
    double imaginary;

    static bool tiny(double d);

public:
    Complex(double r = 0.0, double i = 0.0);
    Complex(const Complex &c) = default;
    ~Complex() = default;

    [[nodiscard]] double re() const noexcept;
    [[nodiscard]] double im() const noexcept;
    [[nodiscard]] bool isZero() const noexcept;
    [[nodiscard]] bool isReal() const noexcept;
    [[nodiscard]] double radius() const;
    double angle() const;

    Complex &operator=(const Complex &c) = default;

    Complex &operator+=(const Complex &c) noexcept;
    Complex &operator+=(double c) noexcept;
    [[nodiscard]] Complex operator+(const Complex &c) const noexcept;
    [[nodiscard]] Complex operator+(double c) const noexcept;

    Complex &operator-=(const Complex &c) noexcept;
    Complex &operator-=(double c) noexcept;
    [[nodiscard]] Complex operator-(const Complex &c) const noexcept;
    [[nodiscard]] Complex operator-(double c) const noexcept;

    Complex &operator*=(const Complex &c) noexcept;
    Complex &operator*=(double c) noexcept;
    [[nodiscard]] Complex operator*(const Complex &c) const noexcept;
    [[nodiscard]] Complex operator*(double c) const noexcept;

    Complex &operator/=(double d);
    Complex &operator/=(const Complex &c);
    [[nodiscard]] Complex operator/(const Complex &c) const;
    [[nodiscard]] Complex operator/(double c) const;
};

bool operator==(const Complex &c1, const Complex &c2);
bool operator!=(const Complex &c1, const Complex &c2);

Complex operator!(const Complex &c);
double abs2(const Complex &c);
double abs(const Complex &c);
Complex sqrt(const Complex &c);

std::ostream &operator<<(std::ostream &os, const Complex &c);