#include "main_app.hpp"

#include <iostream>

#include "mandelbrot.hpp"
#include "terminalcolour.hpp"

int run_interactive_mandelbrot(std::istream &is, std::ostream &os)
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
    const bool is_outside = set.isNotMandelbrot(c);
    const Modifier colour(is_outside ? ForegroundCode::GREEN : ForegroundCode::RED);
    os << "is " << c << " outside set? " << colour << std::boolalpha << is_outside << Modifier()
       << '\n';
    return 0;
}
