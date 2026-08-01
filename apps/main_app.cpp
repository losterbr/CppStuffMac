#include "main_app.hpp"

#include <sstream>

#include "complexnumbers.hpp"
#include "mandelbrot.hpp"
#include "terminalcolour.hpp"

std::string build_main_output()
{
    std::ostringstream out;
    out << Modifier(ForegroundCode::RED, BackgroundCode::GREEN);
    out << Complex();
    out << Modifier() << '\n';

    Mandelbrot set;
    out << "is 0.5+0i outside set? " << std::boolalpha << set.isNotMandelbrot(Complex(0.5, 0.0))
        << '\n';
    return out.str();
}

int run_main_app(std::ostream &os)
{
    os << build_main_output();
    return 0;
}
