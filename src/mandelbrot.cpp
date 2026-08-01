#include "mandelbrot.hpp"

Mandelbrot::Mandelbrot(int max_iterations, bool check_internalpoints)
    : max_iterations(max_iterations), check_internalpoints(check_internalpoints) {}

bool Mandelbrot::inMainCardioid(Complex c) const
{
    // https://iquilezles.org/www/articles/mset_1bulb/mset1bulb.htm
    const double abs_c_squared = abs2(c);
    return ((8.0 * abs_c_squared - 3.0) * abs_c_squared + c.re()) < 3.0 / 32.0;
}

bool Mandelbrot::inPerio2Bulb(Complex c) const
{
    // https://iquilezles.org/www/articles/mset_1bulb/mset1bulb.htm
    const double x = c.re();
    const double y = c.im();
    const double distance_to_minus_one_squared = (x + 1.0) * (x + 1.0) + y * y;
    return distance_to_minus_one_squared < 1.0 / 16.0;
}

int Mandelbrot::iterations(Complex c) const
{
    // Use short-cuts for well-known internal areas of the classical set.
    if (check_internalpoints && (inMainCardioid(c) || inPerio2Bulb(c)))
    {
        return -1;
    }

    int iteration_count = 0;
    Complex z;
    double real2 = 0.0;
    double im2 = 0.0;
    while ((real2 + im2 <= DIVERGENCE_RADIUS_SQUARE) && (iteration_count <= max_iterations))
    {
        z = Complex(real2 - im2 + c.re(), 2.0 * z.re() * z.im() + c.im());

        real2 = z.re() * z.re();
        im2 = z.im() * z.im();
        ++iteration_count;
    }

    if (iteration_count > max_iterations)
    {
        return -1;
    }
    return iteration_count;
}

bool Mandelbrot::isNotMandelbrot(const Complex &c) const
{
    return iterations(c) >= 0;
}

const double Mandelbrot::DIVERGENCE_RADIUS_SQUARE = 4.0;