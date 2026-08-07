#include "complexnumbers.hpp"

#include <cmath>
#include <limits>
#include <numbers>
#include <ostream>
#include <stdexcept>

namespace
{
constexpr double two_epsilon = 2.0 * std::numeric_limits<double>::epsilon();
}

bool Complex::tiny(double d) { return std::abs(d) < two_epsilon; }

Complex::Complex(double r, double i) : real(r), imaginary(i) {}

double Complex::re() const noexcept { return real; }

double Complex::im() const noexcept { return imaginary; }

bool Complex::isZero() const noexcept { return tiny(real) && tiny(imaginary); }

bool Complex::isReal() const noexcept { return tiny(imaginary); }

double Complex::radius() const { return abs(*this); }

double Complex::angle() const
{
    if (isZero())
    {
        throw std::invalid_argument("polar angle not defined at origin");
    }

    if (tiny(imaginary))
    {
        return (real >= 0.0) ? 0.0 : std::numbers::pi;
    }

    if (tiny(real))
    {
        return (imaginary >= 0.0) ? std::numbers::pi / 2.0 : 3.0 * std::numbers::pi / 2.0;
    }

    double theta = std::atan2(imaginary, real);
    if (theta < 0.0)
    {
        theta += 2.0 * std::numbers::pi;
    }
    return theta;
}

bool operator==(const Complex &c1, const Complex &c2)
{
    return c1.isZero() ? c2.isZero()
                       : (std::abs(c1.re() - c2.re()) < two_epsilon &&
                          std::abs(c1.im() - c2.im()) < two_epsilon);
}

bool operator!=(const Complex &c1, const Complex &c2) { return !(c1 == c2); }

Complex operator!(const Complex &c) { return Complex(c.re(), -c.im()); }

double abs2(const Complex &c) { return c.re() * c.re() + c.im() * c.im(); }

double abs(const Complex &c) { return std::sqrt(abs2(c)); }

Complex &Complex::operator+=(const Complex &c) noexcept
{
    real += c.real;
    imaginary += c.imaginary;
    return *this;
}

Complex &Complex::operator+=(double c) noexcept
{
    real += c;
    return *this;
}

Complex Complex::operator+(const Complex &c) const noexcept { return Complex(*this) += c; }

Complex Complex::operator+(double c) const noexcept { return Complex(*this) += c; }

Complex &Complex::operator-=(const Complex &c) noexcept
{
    real -= c.real;
    imaginary -= c.imaginary;
    return *this;
}

Complex &Complex::operator-=(double c) noexcept
{
    real -= c;
    return *this;
}

Complex Complex::operator-(const Complex &c) const noexcept { return Complex(*this) -= c; }

Complex Complex::operator-(double c) const noexcept { return Complex(*this) -= c; }

Complex &Complex::operator*=(const Complex &c) noexcept
{
    // cache c's members: c may alias *this (e.g. z *= z)
    const double c_real = c.real;
    const double c_imaginary = c.imaginary;
    const double prev_real = real;
    real = c_real * prev_real - imaginary * c_imaginary;
    imaginary = prev_real * c_imaginary + imaginary * c_real;
    return *this;
}

Complex &Complex::operator*=(double c) noexcept
{
    real *= c;
    imaginary *= c;
    return *this;
}

Complex Complex::operator*(const Complex &c) const noexcept { return Complex(*this) *= c; }

Complex Complex::operator*(double c) const noexcept { return Complex(*this) *= c; }

Complex &Complex::operator/=(double d)
{
    if (tiny(d))
    {
        throw std::invalid_argument("cannot divide by zero");
    }
    real /= d;
    imaginary /= d;
    return *this;
}

Complex &Complex::operator/=(const Complex &c)
{
    if (c.isZero())
    {
        throw std::invalid_argument("cannot divide by zero");
    }
    // compute before mutating: c may alias *this (e.g. z /= z)
    const double denom = abs2(c);
    *this *= !c;
    *this /= denom;
    return *this;
}

Complex Complex::operator/(const Complex &c) const { return Complex(*this) /= c; }

Complex Complex::operator/(double c) const { return Complex(*this) /= c; }

Complex sqrt(const Complex &c)
{
    if (c.isZero())
    {
        return Complex();
    }

    if (c.isReal())
    {
        if (c.re() > 0.0)
        {
            return Complex(std::sqrt(c.re()));
        }
        if (c.re() < 0.0)
        {
            return Complex(0.0, std::sqrt(-c.re()));
        }
    }

    const double r = abs(c);
    Complex cplusr(c);
    cplusr += r;
    const double abs_cplusr = abs(cplusr);
    const double scale = std::sqrt(r) / abs_cplusr;
    return cplusr * scale;
}

std::ostream &operator<<(std::ostream &os, const Complex &c)
{
    os << c.re() << '+' << c.im() << 'i';
    return os;
}