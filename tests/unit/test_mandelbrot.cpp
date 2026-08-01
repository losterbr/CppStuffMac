#include <iostream>
#include "mandelbrot.hpp"
#include <gtest/gtest.h>

TEST(MandelbrotSuite, notInMandelbrot)
{
    Mandelbrot m;
    const Complex data[]{
        Complex(0.5, 0.),
        Complex(1., 0.),
        Complex(2., 0.),
        Complex(-3., 0.)};
    for (Complex c : data)
    {
        EXPECT_EQ(m.isNotMandelbrot(c), true) << c;
    }
}

TEST(MandelbrotSuite, inMandelbrot)
{
    Mandelbrot m;
    const Complex data[]{
        Complex(0., 0.),
        Complex(-0.5, 0.),
        Complex(-1., 0.),
        Complex(-2., 0.),
        Complex(0., 1.),
        Complex(0., +1.),
        Complex(-1. / 8., 3. / 4),
        Complex(-1. / 8., -3. / 4),
    };
    for (Complex c : data)
    {
        EXPECT_EQ(m.isNotMandelbrot(c), false) << c;
    }
}

TEST(MandelbrotSuite, iterationsForKnownExteriorPoint)
{
    Mandelbrot m;
    EXPECT_EQ(m.iterations(Complex(2.0, 0.0)), 2);
}

TEST(MandelbrotSuite, iterationsForKnownInteriorPoint)
{
    Mandelbrot m;
    EXPECT_EQ(m.iterations(Complex(0.0, 0.0)), -1);
}

TEST(MandelbrotSuite, membershipWithInternalShortcutsDisabled)
{
    Mandelbrot m(1000, false);
    EXPECT_TRUE(m.isNotMandelbrot(Complex(0.5, 0.0)));
    EXPECT_FALSE(m.isNotMandelbrot(Complex(0.0, 0.0)));
}
