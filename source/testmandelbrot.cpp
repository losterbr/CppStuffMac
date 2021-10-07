#include <iostream>
#include "mandelbrot.cpp"
#include <gtest/gtest.h>

TEST(IntegerInputsSuite, notInMandelbrot)
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

TEST(IntegerInputsSuite, inMandelbrot)
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

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}