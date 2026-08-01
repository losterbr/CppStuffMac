#include <iostream>
#include "complexnumbers.hpp"
#include "mandelbrot.hpp"
#include "terminalcolour.hpp"

int main()
{
    std::cout << Modifier(ForegroundCode::RED, BackgroundCode::GREEN);
    std::cout << Complex();
    std::cout << Modifier() << '\n';

    Mandelbrot set;
    std::cout << "is 0.5+0i outside set? " << std::boolalpha
              << set.isNotMandelbrot(Complex(0.5, 0.0)) << '\n';
}