#include "main_app.hpp"

#include <iostream>

#include "mandelbrot.hpp"

int run_main_app_interactive(std::istream &is, std::ostream &os)
{
    Mandelbrot set;

    double real = 0.0;
    os << "Enter real part: ";
    if (!(is >> real))
    {
        os << "Invalid input for real part." << '\n';
        return 1;
    }

    double imaginary = 0.0;
    os << "Enter imaginary part: ";
    if (!(is >> imaginary))
    {
        os << "Invalid input for imaginary part." << '\n';
        return 1;
    }

    const Complex c(real, imaginary);
    os << "is " << c << " outside set? " << std::boolalpha << set.isNotMandelbrot(c) << '\n';
    return 0;
}
