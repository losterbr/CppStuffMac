#include <iostream>
#include <vector>
#include <string>
#include "complexnumbers.cpp"

class Mandelbrot
{
    int max_iterations;
    bool check_internalpoints;
    static const double DIVERGENCE_RADIUS_SQUARE;
    static const int default_max_iterations = 1000;

public:
    Mandelbrot(int max_iterations = default_max_iterations,
               bool check_internalpoints = true)
        : max_iterations(max_iterations),
          check_internalpoints(check_internalpoints) {}
    Mandelbrot(const Mandelbrot &m) : max_iterations(m.max_iterations) {}
    ~Mandelbrot() {}

    inline bool inMainCardioid(const Complex c)
    {
        // https://iquilezles.org/www/articles/mset_1bulb/mset1bulb.htm
        double absc2 = abs2(c);
        return ((8. * absc2 - 3.) * absc2 + c.re()) < 3. / 32.;
    }

    inline bool inPerio2Bulb(const Complex c)
    {
        // https://iquilezles.org/www/articles/mset_1bulb/mset1bulb.htm
        double abscplus12 = c.real * c.real + c.imaginary * c.imaginary + 1.;
        return abscplus12 < 0.25;
    }

    const int iterations(const Complex c) // use option-type. could not make it compile c17?
    {
        // when we are looking at the classical set, i.e., not zooming-in,
        // it make sense to use the below short-cut
        if (check_internalpoints &&
            (inMainCardioid(c) || inPerio2Bulb(c)))
            return -1;

        int iteration_count(0);
        Complex z;
        double real2(0.), im2(0.);
        while ((real2 + im2 <= DIVERGENCE_RADIUS_SQUARE) && (iteration_count <= max_iterations))
        {
            z.imaginary = 2. * z.real * z.imaginary + c.imaginary;
            z.real = real2 - im2 + c.real;

            real2 = z.real * z.real;
            im2 = z.imaginary * z.imaginary;
            ++iteration_count;
        };
        if (iteration_count > max_iterations)
            return -1;
        return iteration_count;
    }
    // note that the return value false does not imply that it is in the Mandelbrot set
    const bool isNotMandelbrot(const Complex &c)
    {
        int i(iterations(c));
        return (i >= 0); // Reached divergence before max-iter
    }
};

const double Mandelbrot::DIVERGENCE_RADIUS_SQUARE = 4.;