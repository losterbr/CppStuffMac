#include "main_app.hpp"

#include <iostream>

#include "complexnumbers.hpp"
#include "mandelbrot.hpp"
#include "terminalcolour.hpp"

int run_main_app_interactive(std::istream &is, std::ostream &os)
{
    os << Modifier(ForegroundCode::RED, BackgroundCode::GREEN);
    os << Complex();
    os << Modifier() << '\n';

    Mandelbrot set;
    os << "is 0.5+0i outside set? " << std::boolalpha << set.isNotMandelbrot(Complex(0.5, 0.0))
       << '\n';

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
