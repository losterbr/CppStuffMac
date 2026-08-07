#include "mandelbrot.hpp"

Mandelbrot::Mandelbrot(int iterations, bool check_internal)
    : max_iterations(iterations), check_internalpoints(check_internal) {}

bool Mandelbrot::inMainCardioid(const Complex &c) const
{
    // https://iquilezles.org/www/articles/mset_1bulb/mset1bulb.htm
    const double abs_c_squared = abs2(c);
    return ((8.0 * abs_c_squared - 3.0) * abs_c_squared + c.re()) < 3.0 / 32.0;
}

bool Mandelbrot::inPerio2Bulb(const Complex &c) const
{
    // https://iquilezles.org/www/articles/mset_1bulb/mset1bulb.htm
    const double x = c.re();
    const double y = c.im();
    const double distance_to_minus_one_squared = (x + 1.0) * (x + 1.0) + y * y;
    return distance_to_minus_one_squared < 1.0 / 16.0;
}

int Mandelbrot::iterations(const Complex &c) const
{
    // Use short-cuts for well-known internal areas of the classical set.
    if (check_internalpoints && (inMainCardioid(c) || inPerio2Bulb(c)))
    {
        return -1;
    }

    const double c_re = c.re();
    const double c_im = c.im();

    int iteration_count = 0;
    double z_re = 0.0;
    double z_im = 0.0;
    double real2 = 0.0;
    double im2 = 0.0;
    while ((real2 + im2 <= DIVERGENCE_RADIUS_SQUARE) && (iteration_count <= max_iterations))
    {
        z_im = 2.0 * z_re * z_im + c_im;
        z_re = real2 - im2 + c_re;

        real2 = z_re * z_re;
        im2 = z_im * z_im;
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