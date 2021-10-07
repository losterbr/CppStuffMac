#include <stdio.h>
#include <iostream>
#include <limits>
#include <math.h>

constexpr double epsilon = 2. * std::numeric_limits<double>::epsilon();

class Complex
{
    friend class Mandelbrot;
    double real;
    double imaginary;
    inline static bool tiny(const double &d) { return abs(d) < epsilon; }

public:
    Complex(double r = 0., double i = 0.) : real(r), imaginary(i) {}
    Complex(const Complex &c) : real(c.real), imaginary(c.imaginary) {}
    ~Complex() {}

    double re() const { return real; }
    double im() const { return imaginary; }
    inline bool isZero() const { return (tiny(real) && tiny(imaginary)); }
    inline bool isReal() const { return tiny(imaginary); }
    inline double radius() const { return abs(*this); }
    double angle() const
    {
        if (isZero())
            throw std::invalid_argument("polar angle not defined at origin");
        if (tiny(imaginary))
        {
            if (real >= 0)
            {
                return 0.;
            }
            else
            {
                return M_PI;
            }
        }
        if (tiny(real))
        {
            if (imaginary >= 0)
            {
                return M_PI_2;
            }
            else
            {
                return 3. * M_PI_2;
            }
        }
        return acos(real / radius());
    }
    const Complex &operator=(const Complex &c)
    {
        real = c.real;
        imaginary = c.imaginary;
        return *this;
    }
    // comparison
    friend bool operator==(const Complex &c1, const Complex &c2)
    {
        if (tiny(c1.real - c2.real) && tiny(c1.imaginary - c2.imaginary))
        {
            return true;
        }
        else
        {
            return false;
        };
    }
    friend bool operator!=(const Complex &c1, const Complex &c2)
    {
        if (tiny(c1.real - c2.real) && tiny(c1.imaginary - c2.imaginary))
        {
            return false;
        }
        else
        {
            return true;
        };
    }
    // complex-specific
    friend Complex operator!(const Complex &c)
    {
        return Complex(c.re(), -c.im());
    }
    friend double abs2(const Complex &c)
    {
        return c.re() * c.re() + c.im() * c.im();
    }
    friend double abs(const Complex &c)
    {
        return sqrt(c.re() * c.re() + c.im() * c.im());
    }
    // Addition
    const Complex &operator+=(const Complex &c)
    {
        real += c.real;
        imaginary += c.imaginary;
        return *this;
    }
    const Complex &operator+=(const double &c)
    {
        real += c;
        return *this;
    }
    const Complex operator+(const Complex &c)
    {
        return Complex(this->re() + c.re(), this->im() + c.im());
    }
    const Complex operator+(const double &c)
    {
        return Complex(this->re() + c, this->im());
    }
    // subtraction
    const Complex &operator-=(const Complex &c)
    {
        real -= c.real;
        imaginary -= c.imaginary;
        return *this;
    }
    const Complex &operator-=(const double &c)
    {
        real -= c;
        return *this;
    }
    const Complex operator-(const Complex &c)
    {
        return Complex(this->re() - c.re(), this->im() - c.im());
    }
    const Complex operator-(const double &c)
    {
        return Complex(this->re() - c, this->im());
    }
    // multiplication
    const Complex &operator*=(const Complex &c)
    {
        double prevreal = real;
        real = c.real * real - imaginary * c.imaginary;
        imaginary = prevreal * c.imaginary + imaginary * c.real;
        return *this;
    }
    const Complex &operator*=(const double &c)
    {
        real = real * c;
        imaginary = imaginary * c;
        return *this;
    }
    const Complex operator*(const Complex &c)
    {
        return Complex(*this) *= c;
    }
    const Complex operator*(const double &c)
    {
        return Complex(*this) *= c;
    }
    // division
    const Complex &operator/=(double d)
    {
        if (tiny(d))
            throw std::invalid_argument("cannot divide by zero");
        real /= d;
        imaginary /= d;
        return *this;
    }
    const Complex &operator/=(const Complex &c)
    {
        if (c.isZero())
            throw std::invalid_argument("cannot divide by zero");
        return *this *= (!c) /= abs2(c); // a/b=a*!b/|b|^2
    }
    const Complex operator/(const Complex &c)
    {
        return Complex(*this) /= c;
    }
    const Complex operator/(const double &c)
    {
        return Complex(*this) /= c;
    }
    friend Complex sqrt(const Complex &c) // remove x
    {
        // principal square root
        if (c.isZero())
        {
            return Complex();
        }
        if (c.isReal())
        {
            if (c.re() > 0.)
            {
                return Complex(sqrt(c.re()));
            }
            if (c.re() < 0.)
            {
                return Complex(0., sqrt(-c.re()));
            }
        }
        // TODO: needs some clean-up
        const double r(abs(c));
        Complex cplusr(c);
        cplusr += r;
        double abscplusr(abs(cplusr));
        double scale(sqrt(r) / abscplusr);
        return cplusr * scale;
    }
};

std::ostream &operator<<(std::ostream &os, const Complex &c)
{
    os << c.re() << '+' << c.im() << 'i';
    return os;
}