#include <cmath>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include <gtest/gtest.h>

#include "main_app.hpp"
#include "plotting_app.hpp"
#include "terminalcolour.hpp"

namespace
{
std::string read_file(const std::string &file_path)
{
    std::ifstream in(file_path);
    std::ostringstream out;
    out << in.rdbuf();
    return out.str();
}
} // namespace

TEST(InteractiveMandelbrotSuite, PromptsAndEvaluatesInput)
{
    std::istringstream in("0.5 0\n");
    std::ostringstream out;
    EXPECT_EQ(run_interactive_mandelbrot(in, out), 0);
    EXPECT_NE(out.str().find("Enter real part:"), std::string::npos);
    EXPECT_NE(out.str().find("Enter imaginary part:"), std::string::npos);
    EXPECT_NE(out.str().find("is 0.5+0i outside set? true"), std::string::npos);
}

TEST(InteractiveMandelbrotSuite, WritesOutput)
{
    std::istringstream in("0.5 0\n");
    std::ostringstream out;
    EXPECT_EQ(run_interactive_mandelbrot(in, out), 0);
    EXPECT_FALSE(out.str().empty());
    EXPECT_NE(out.str().find("Enter real part:"), std::string::npos);
    EXPECT_NE(out.str().find("Enter imaginary part:"), std::string::npos);
    EXPECT_NE(out.str().find("is 0.5+0i outside set? true"), std::string::npos);
}

TEST(InteractiveMandelbrotSuite, RejectsInvalidRealInput)
{
    std::istringstream in("abc 0\n");
    std::ostringstream out;
    EXPECT_EQ(run_interactive_mandelbrot(in, out), 1);
    EXPECT_NE(out.str().find("Invalid input for real part."), std::string::npos);
}

TEST(InteractiveMandelbrotSuite, RejectsInvalidImaginaryInput)
{
    std::istringstream in("0.5 abc\n");
    std::ostringstream out;
    EXPECT_EQ(run_interactive_mandelbrot(in, out), 1);
    EXPECT_NE(out.str().find("Invalid input for imaginary part."), std::string::npos);
}

TEST(TerminalColourSuite, ModifierStoresForegroundAndBackground)
{
    const Modifier modifier(ForegroundCode::RED, BackgroundCode::GREEN);
    EXPECT_EQ(modifier.foreground(), ForegroundCode::RED);
    EXPECT_EQ(modifier.background(), BackgroundCode::GREEN);
}

TEST(TerminalColourSuite, ModifierDefaultCodesAreUsed)
{
    const Modifier modifier;
    EXPECT_EQ(modifier.foreground(), ForegroundCode::DEFAULT);
    EXPECT_EQ(modifier.background(), BackgroundCode::DEFAULT);
}

TEST(TerminalColourSuite, ModifierStreamOutputsAnsiCodes)
{
    std::ostringstream out;
    out << Modifier(ForegroundCode::BLUE, BackgroundCode::RED);
    EXPECT_EQ(out.str(), "\033[34m\033[41m");
}

TEST(PlottingAppSuite, BuildXDataProducesExpectedRange)
{
    const std::vector<double> x = build_x_data(4, 1.0);
    ASSERT_EQ(x.size(), 5U);
    EXPECT_DOUBLE_EQ(x.front(), 0.0);
    EXPECT_NEAR(x.back(), 1.0, 1e-12);
}

TEST(PlottingAppSuite, BuildXDataRejectsInvalidInput)
{
    EXPECT_THROW(build_x_data(0, 1.0), std::invalid_argument);
    EXPECT_THROW(build_x_data(2, 0.0), std::invalid_argument);
}

TEST(PlottingAppSuite, BuildYDataMatchesFormula)
{
    const std::vector<double> x{0.0, 0.25, 0.5};
    const std::vector<double> y = build_y_data(x);
    ASSERT_EQ(y.size(), x.size());
    for (size_t i = 0; i < x.size(); ++i)
    {
        EXPECT_NEAR(y[i], std::sin(x[i]) * std::cos(10.0 * x[i]), 1e-12);
    }
}

TEST(PlottingAppSuite, WritePlotDataWritesRows)
{
    const std::string path = "test_plot_data.txt";
    const std::vector<double> x{0.0, 0.5};
    const std::vector<double> y{1.0, 2.0};

    write_plot_data(path, x, y);
    const std::string content = read_file(path);
    EXPECT_NE(content.find("0 1"), std::string::npos);
    EXPECT_NE(content.find("0.5 2"), std::string::npos);
    std::remove(path.c_str());
}

TEST(PlottingAppSuite, WritePlotDataRejectsMismatchedVectors)
{
    const std::vector<double> x{0.0};
    const std::vector<double> y{1.0, 2.0};
    EXPECT_THROW(write_plot_data("invalid.txt", x, y), std::invalid_argument);
}

TEST(PlottingAppSuite, WritePlotDataThrowsWhenFileCannotBeOpened)
{
    const std::vector<double> x{0.0};
    const std::vector<double> y{1.0};
    EXPECT_THROW(write_plot_data("does-not-exist-dir/out.txt", x, y), std::runtime_error);
}

TEST(PlottingAppSuite, RunPlottingAppCreatesAndCleansFile)
{
    PlotOptions options;
    options.intervals = 4;
    options.interval_size = 1.0;
    options.temp_file = "test_run_plotting.txt";
    options.invoke_gnuplot = false;

    EXPECT_EQ(run_plotting_app(options), 0);

    std::ifstream in(options.temp_file);
    EXPECT_FALSE(in.good()) << "temp file should be removed after run";
}

TEST(PlottingAppSuite, RunPlottingAppSkipsGnuplotWhenDisabledByEnv)
{
    PlotOptions options;
    options.intervals = 4;
    options.interval_size = 1.0;
    options.temp_file = "test_run_plotting_env.txt";
    options.invoke_gnuplot = true;

    setenv("PLOTTING_APP_NO_GNUPLOT", "1", 1);
    EXPECT_EQ(run_plotting_app(options), 0);
    unsetenv("PLOTTING_APP_NO_GNUPLOT");

    std::ifstream in(options.temp_file);
    EXPECT_FALSE(in.good()) << "temp file should be removed after run";
}
