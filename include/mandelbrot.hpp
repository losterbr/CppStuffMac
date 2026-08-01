#pragma once

#include "complexnumbers.hpp"

class Mandelbrot
{
    int max_iterations;
    bool check_internalpoints;

    static const double DIVERGENCE_RADIUS_SQUARE;
    static const int default_max_iterations = 1000;

    bool inMainCardioid(const Complex &c) const;
    bool inPerio2Bulb(const Complex &c) const;

public:
    explicit Mandelbrot(int max_iterations = default_max_iterations,
                        bool check_internalpoints = true);
    Mandelbrot(const Mandelbrot &m) = default;
    ~Mandelbrot() = default;

    int iterations(const Complex &c) const;
    bool isNotMandelbrot(const Complex &c) const;
};