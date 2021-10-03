#include <iostream>
#include "complexnumbers.cpp"
#include <gtest/gtest.h>

TEST(IntegerInputsSuite, constructor)
{
  Complex actual;
  EXPECT_EQ(actual.im(), 0.) << actual;
  EXPECT_EQ(actual.re(), 0.) << actual;
}
TEST(IntegerInputsSuite, basics)
{
  Complex c(0., 0.);
  EXPECT_EQ(c.isZero(), true) << c;
  EXPECT_EQ(c.im(), 0.) << c;
  EXPECT_EQ(c.re(), 0.) << c;
  EXPECT_EQ(c.isReal(), true) << c;
  EXPECT_EQ(Complex(1., 1.).isReal(), false) << c;
}

TEST(IntegerInputsSuite, basicsPolar)
{
  EXPECT_EQ(Complex().radius(), 0.) << "check is zero radius";
  EXPECT_THROW(Complex().angle(), std::invalid_argument) << "check throws";
  EXPECT_EQ(Complex(0., 1.).angle(), M_PI_2) << "check angle";
  EXPECT_EQ(Complex(-1., 0.).angle(), M_PI) << "check angle";
  EXPECT_EQ(Complex(0., -1.).angle(), 3. * M_PI_2) << "check angle";
  EXPECT_EQ(Complex(1., 1.).radius(), M_SQRT2) << "check 1+i";
  EXPECT_TRUE(abs(Complex(1., 1.).angle() - M_PI_2 / 2.) < std::numeric_limits<double>::epsilon()) << "check 1+i";
}

TEST(IntegerInputsSuite, copyConstructor)
{
  Complex original(5., 99.);
  Complex copy(original);
  EXPECT_EQ(original.im(), copy.im()) << original << copy;
  EXPECT_EQ(original.re(), copy.re()) << original << copy;
}
// comparison
TEST(IntegerInputsSuite, equality)
{
  EXPECT_EQ(Complex() == Complex(1., 1.), false) << "check equality";
  EXPECT_EQ(Complex() == Complex(0., 1.), false) << "check equality";
  EXPECT_EQ(Complex() == Complex(1., 0.), false) << "check equality";
  EXPECT_EQ(Complex() == Complex(0., 0.), true) << "check equality";
}

TEST(IntegerInputsSuite, inequality)
{
  EXPECT_EQ(Complex() != Complex(1., 1.), true) << "check equality";
  EXPECT_EQ(Complex() != Complex(0., 1.), true) << "check equality";
  EXPECT_EQ(Complex() != Complex(1., 0.), true) << "check equality";
  EXPECT_EQ(Complex() != Complex(0., 0.), false) << "check equality";
}
// specific
TEST(IntegerInputsSuite, conjugate)
{
  EXPECT_EQ(!Complex(2., 3.), Complex(2., -3.)) << "check equality";
  EXPECT_EQ(!Complex(2., 0.), Complex(2., 0)) << "check equality";
  EXPECT_EQ(!Complex(0., 3.), Complex(0., -3.)) << "check equality";
}

TEST(IntegerInputsSuite, absSquare)
{
  EXPECT_EQ(abs2(Complex(2., 3.)), 13.) << "check equality";
  EXPECT_EQ(abs2(Complex(-1., 0.)), 1.) << "check equality";
  EXPECT_EQ(abs2(Complex(0., -1.)), 1.) << "check equality";
}

TEST(IntegerInputsSuite, abs)
{
  EXPECT_EQ(abs(Complex(3., 4.)), 5.) << "check equality";
  EXPECT_EQ(abs(Complex(-1., 0.)), 1.) << "check equality";
  EXPECT_EQ(abs(Complex(0., -1.)), 1.) << "check equality";
}

// Additions
TEST(IntegerInputsSuite, additionAsignment)
{
  EXPECT_EQ(Complex(2., 3.) += Complex(1., 1.), Complex(3., 4.)) << "check equality";
  EXPECT_EQ(Complex(-2., 3.) += Complex(1., 1.), Complex(-1., 4.)) << "check equality";
  EXPECT_EQ(Complex(-2., 3.) += Complex(0., 0.), Complex(-2., 3.)) << "check equality";
}
TEST(IntegerInputsSuite, additionAsignmentReal)
{
  EXPECT_EQ(Complex(2., 3.) += 1., Complex(3., 3.)) << "check equality";
  EXPECT_EQ(Complex(-2., 3.) += 1., Complex(-1., 3.)) << "check equality";
  EXPECT_EQ(Complex(-2., 3.) += 0., Complex(-2., 3.)) << "check equality";
}
TEST(IntegerInputsSuite, addition)
{
  EXPECT_EQ(Complex(2., 3.) + Complex(1., 0.), Complex(3., 3.)) << "check equality";
  EXPECT_EQ(Complex(2., 3.) + Complex(0., 1.), Complex(2., 4.)) << "check equality";
  EXPECT_EQ(Complex(0., 1.) + Complex(0., 1.), Complex(0., 2.)) << "check equality";
  EXPECT_EQ(Complex(2., 2.) + Complex(2., 2.), Complex(4., 4.)) << "check equality";
  // check for side effects
  Complex a(1., 2.), b(3., 4.);
  EXPECT_EQ(a + b, Complex(4., 6.)) << "check equality";
  EXPECT_EQ(a, Complex(1., 2.)) << "check equality";
  EXPECT_EQ(b, Complex(3., 4.)) << "check equality";
}
TEST(IntegerInputsSuite, additionReal)
{
  EXPECT_EQ(Complex(2., 3.) + 1., Complex(3., 3.)) << "check equality";
  // check for side effects
  Complex a(1., 2.);
  double b(3.);
  EXPECT_EQ(a + b, Complex(4., 2.)) << "check equality";
  EXPECT_EQ(a, Complex(1., 2.)) << "check equality";
  EXPECT_EQ(b, 3.) << "check equality";
}

// subtractions
TEST(IntegerInputsSuite, subtractionAsignment)
{
  EXPECT_EQ(Complex(2., 3.) -= Complex(1., 1.), Complex(1., 2.)) << "check equality";
  EXPECT_EQ(Complex(-2., 3.) -= Complex(1., 1.), Complex(-3., 2.)) << "check equality";
  EXPECT_EQ(Complex(-2., 3.) -= Complex(0., 0.), Complex(-2., 3.)) << "check equality";
}

TEST(IntegerInputsSuite, subtractionAsignmentReal)
{
  EXPECT_EQ(Complex(2., 3.) -= 1., Complex(1., 3.)) << "check equality";
  EXPECT_EQ(Complex(-2., 3.) -= 1., Complex(-3., 3.)) << "check equality";
  EXPECT_EQ(Complex(-2., 3.) -= 0., Complex(-2., 3.)) << "check equality";
}

TEST(IntegerInputsSuite, subtraction)
{
  EXPECT_EQ(Complex(2., 3.) - Complex(1., 0.), Complex(1., 3.)) << "check equality";
  EXPECT_EQ(Complex(2., 3.) - Complex(0., 1.), Complex(2., 2.)) << "check equality";
  EXPECT_EQ(Complex(0., 1.) - Complex(0., 1.), Complex(0., 0.)) << "check equality";
  EXPECT_EQ(Complex(2., 2.) - Complex(-2., -2.), Complex(4., 4.)) << "check equality";
  // check for side effects
  Complex a(1., 2.), b(3., 4.);
  EXPECT_EQ(a - b, Complex(-2., -2.)) << "check equality";
  EXPECT_EQ(a, Complex(1., 2.)) << "check equality";
  EXPECT_EQ(b, Complex(3., 4.)) << "check equality";
}

TEST(IntegerInputsSuite, subtractionReal)
{
  EXPECT_EQ(Complex(2., 3.) - 1., Complex(1., 3.)) << "check equality";
  EXPECT_EQ(Complex(2., 3.) - 0., Complex(2., 3.)) << "check equality";
  EXPECT_EQ(Complex(0., 1.) - 0., Complex(0., 1.)) << "check equality";
  EXPECT_EQ(Complex(2., 2.) - (-2.), Complex(4., 2.)) << "check equality";
  // check for side effects
  Complex a(1., 2.);
  double b(3.);
  EXPECT_EQ(a - b, Complex(-2., 2.)) << "check equality";
  EXPECT_EQ(a, Complex(1., 2.)) << "check equality";
  EXPECT_EQ(b, 3.) << "check equality";
}

// multiplication
TEST(IntegerInputsSuite, multiplicationAsignment)
{
  EXPECT_EQ(Complex(2., 3.) *= Complex(1., 0.), Complex(2., 3.)) << "check equality";
  EXPECT_EQ(Complex(2., 3.) *= Complex(0., 1.), Complex(-3., 2.)) << "check equality";
  EXPECT_EQ(Complex(0., 1.) *= Complex(0., 1.), Complex(-1., 0.)) << "check equality";
  EXPECT_EQ(Complex(2., 2.) *= Complex(2., 2.), Complex(0., 8.)) << "check equality";
}
TEST(IntegerInputsSuite, multiplicationAsignmentReal)
{
  EXPECT_EQ(Complex(2., 3.) *= 0., Complex(0., 0.)) << "check equality";
  EXPECT_EQ(Complex(2., 3.) *= 1., Complex(2., 3.)) << "check equality";
  EXPECT_EQ(Complex(2., 2.) *= (-2.), Complex(-4., -4.)) << "check equality";
}
TEST(IntegerInputsSuite, multiplication)
{
  EXPECT_EQ(Complex(2., 3.) * Complex(1., 0.), Complex(2., 3.)) << "check equality";
  EXPECT_EQ(Complex(2., 3.) * Complex(0., 1.), Complex(-3., 2.)) << "check equality";
  EXPECT_EQ(Complex(0., 1.) * Complex(0., 1.), Complex(-1., 0.)) << "check equality";
  EXPECT_EQ(Complex(2., 2.) * Complex(-2., -2.), Complex(0., -8.)) << "check equality";
  // check for side effects
  Complex a(1., 2.), b(3., 4.);
  EXPECT_EQ(a * b, Complex(-5., 10.)) << "check equality";
  EXPECT_EQ(a, Complex(1., 2.)) << "check equality";
  EXPECT_EQ(b, Complex(3., 4.)) << "check equality";
}
TEST(IntegerInputsSuite, multiplicationReal)
{
  EXPECT_EQ(Complex(2., 3.) * 0., Complex(0., 0.)) << "check equality";
  EXPECT_EQ(Complex(2., 3.) * 1., Complex(2., 3.)) << "check equality";
  EXPECT_EQ(Complex(0., 1.) * 2., Complex(0., 2.)) << "check equality";
  EXPECT_EQ(Complex(2., 2.) * (-2.), Complex(-4., -4.)) << "check equality";
  // check for side effects
  Complex a(1., 2.);
  double b(3.);
  EXPECT_EQ(a * b, Complex(3., 6.)) << "check equality";
  EXPECT_EQ(a, Complex(1., 2.)) << "check equality";
  EXPECT_EQ(b, 3.) << "check equality";
}
// division
TEST(IntegerInputsSuite, divisionAsignment)
{
  EXPECT_EQ(Complex(2., 3.) /= Complex(1., 0.), Complex(2., 3.)) << "check equality";
  EXPECT_EQ(Complex(2., 3.) /= Complex(0., 1.), Complex(3., -2.)) << "check equality";
  EXPECT_EQ(Complex(0., 1.) /= Complex(0., 1.), Complex(1., 0.)) << "check equality";
  EXPECT_EQ(Complex(2., 2.) /= Complex(2., 2.), Complex(1., 0.)) << "check equality";
  EXPECT_THROW(Complex(2., 2.) /= Complex(), std::invalid_argument) << "check throws";
}

TEST(IntegerInputsSuite, divisionAsignmentReal)
{
  EXPECT_EQ(Complex(2., 3.) /= 1., Complex(2., 3.)) << "check equality";
  EXPECT_EQ(Complex(2., 4.) /= 2., Complex(1., 2.)) << "check equality";
  EXPECT_EQ(Complex(0., 2.) /= 2., Complex(0., 1.)) << "check equality";
  EXPECT_EQ(Complex(2., 2.) /= 2., Complex(1., 1.)) << "check equality";
  EXPECT_THROW(Complex(2., 2.) /= 0., std::invalid_argument) << "check throws";
}

TEST(IntegerInputsSuite, division)
{
  EXPECT_EQ(Complex(2., 3.) / Complex(1., 0.), Complex(2., 3.)) << "check equality";
  EXPECT_EQ(Complex(2., 3.) / Complex(0., 1.), Complex(3., -2.)) << "check equality";
  EXPECT_EQ(Complex(0., 1.) / Complex(0., 1.), Complex(1., 0.)) << "check equality";
  EXPECT_EQ(Complex(2., 2.) / Complex(-2., -2.), Complex(-1., 0.)) << "check equality";
  // check for side effects
  Complex a(4., 4.), b(2., 0.);
  EXPECT_EQ(a / b, Complex(2., 2.)) << "check equality";
  EXPECT_EQ(a, Complex(4., 4.)) << "check equality";
  EXPECT_EQ(b, Complex(2., 0.)) << "check equality";
}
TEST(IntegerInputsSuite, divisionReal)
{
  EXPECT_EQ(Complex(2., 3.) / 1., Complex(2., 3.)) << "check equality";
  EXPECT_EQ(Complex(2., 4.) / 2., Complex(1., 2.)) << "check equality";
  EXPECT_EQ(Complex(0., 1.) / 1., Complex(0., 1.)) << "check equality";
  EXPECT_EQ(Complex(1., 0.) / 1., Complex(1., 0.)) << "check equality";
  EXPECT_EQ(Complex(2., 2.) / -2., Complex(-1., -1.)) << "check equality";
  // check for side effects
  Complex a(4., 4.);
  double b(2.);
  EXPECT_EQ(a / b, Complex(2., 2.)) << "check equality";
  EXPECT_EQ(a, Complex(4., 4.)) << "check equality";
  EXPECT_EQ(b, 2.) << "check equality";
}
// sqrt
TEST(IntegerInputsSuite, sqrt)
{
  EXPECT_EQ(sqrt(Complex(0., 0.)), Complex(0., 0.)) << "check equality";
  EXPECT_EQ(sqrt(Complex(1., 0.)), Complex(1., 0.)) << "check equality";
  EXPECT_EQ(sqrt(Complex(4., 0.)), Complex(2., 0.)) << "check equality";
  EXPECT_EQ(sqrt(Complex(-1., 0.)), Complex(0., 1.)) << "check equality";

  const Complex data[]{Complex(1., 1.), Complex(-1., -1.), Complex(1000., 2000.)};
  for (Complex c : data)
  {
    EXPECT_EQ(sqrt(c) * sqrt(c), c) << c;
  }
}
// stream
TEST(IntegerInputsSuite, ostream)
{
  std::ostringstream out;
  Complex c;
  out << c;
  EXPECT_EQ("0+0i", out.str()) << "check equality";
}

int main(int argc, char **argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}