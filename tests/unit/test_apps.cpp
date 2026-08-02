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

TEST(PlottingAppSuite, BuildMandelbrotImageProducesExpectedSize)
{
    PlotOptions options;
    options.mandelbrot_mode = true;
    options.width = 7;
    options.height = 5;
    options.max_iterations = 50;

    const std::vector<int> pixels = build_mandelbrot_image(options);
    ASSERT_EQ(pixels.size(), 35U);
}

TEST(PlottingAppSuite, BuildMandelbrotImageRejectsInvalidBounds)
{
    PlotOptions options;
    options.mandelbrot_mode = true;
    options.width = 10;
    options.height = 10;
    options.x_min = 1.0;
    options.x_max = -1.0;

    EXPECT_THROW(build_mandelbrot_image(options), std::invalid_argument);
}

TEST(PlottingAppSuite, BuildMandelbrotImageRejectsInvalidDimensions)
{
    PlotOptions options;
    options.mandelbrot_mode = true;
    options.width = 0;
    options.height = 10;

    EXPECT_THROW(build_mandelbrot_image(options), std::invalid_argument);
}

TEST(PlottingAppSuite, BuildMandelbrotImageRejectsInvalidIterationCount)
{
    PlotOptions options;
    options.mandelbrot_mode = true;
    options.width = 10;
    options.height = 10;
    options.max_iterations = 0;

    EXPECT_THROW(build_mandelbrot_image(options), std::invalid_argument);
}

TEST(PlottingAppSuite, BuildMandelbrotImageSupportsSinglePixelGrid)
{
    PlotOptions options;
    options.mandelbrot_mode = true;
    options.width = 1;
    options.height = 1;
    options.max_iterations = 20;

    const std::vector<int> pixels = build_mandelbrot_image(options);
    ASSERT_EQ(pixels.size(), 1U);
}

TEST(PlottingAppSuite, BuildMandelbrotImageMarksOriginAsInside)
{
    PlotOptions options;
    options.mandelbrot_mode = true;
    options.width = 3;
    options.height = 3;
    options.max_iterations = 30;
    options.x_min = -1.0;
    options.x_max = 1.0;
    options.y_min = -1.0;
    options.y_max = 1.0;

    const std::vector<int> pixels = build_mandelbrot_image(options);
    const int center = pixels[4];
    EXPECT_EQ(center, options.max_iterations + 1);
}

TEST(PlottingAppSuite, WriteMandelbrotImageDataWritesMatrix)
{
    const std::string path = "test_mandelbrot_matrix.txt";
    const std::vector<int> pixels{1, 2, 3, 4, 5, 6};
    PlotOptions options;
    options.width = 3;
    options.height = 2;
    options.x_min = -1.0;
    options.x_max = 1.0;
    options.y_min = -1.0;
    options.y_max = 1.0;

    write_mandelbrot_image_data(path, pixels, options);
    const std::string content = read_file(path);
    EXPECT_NE(content.find("-1 1 1"), std::string::npos);
    EXPECT_NE(content.find("1 1 3"), std::string::npos);
    EXPECT_NE(content.find("-1 -1 4"), std::string::npos);
    EXPECT_NE(content.find("1 -1 6"), std::string::npos);
    std::remove(path.c_str());
}

TEST(PlottingAppSuite, WriteMandelbrotImageDataRejectsMismatchedSize)
{
    const std::vector<int> pixels{1, 2, 3};
    PlotOptions options;
    options.width = 2;
    options.height = 2;
    EXPECT_THROW(write_mandelbrot_image_data("invalid_matrix.txt", pixels, options),
                 std::invalid_argument);
}

TEST(PlottingAppSuite, WriteMandelbrotImageDataRejectsInvalidDimensions)
{
    const std::vector<int> pixels{1};
    PlotOptions options;
    options.width = 0;
    options.height = 1;

    EXPECT_THROW(write_mandelbrot_image_data("invalid_matrix_dims.txt", pixels, options),
                 std::invalid_argument);
}

TEST(PlottingAppSuite, WriteMandelbrotImageDataRejectsInvalidBounds)
{
    const std::vector<int> pixels{1};
    PlotOptions options;
    options.width = 1;
    options.height = 1;
    options.x_min = 2.0;
    options.x_max = -2.0;

    EXPECT_THROW(write_mandelbrot_image_data("invalid_matrix_bounds.txt", pixels, options),
                 std::invalid_argument);
}

TEST(PlottingAppSuite, WriteMandelbrotImageDataThrowsWhenFileCannotBeOpened)
{
    const std::vector<int> pixels{1};
    PlotOptions options;
    options.width = 1;
    options.height = 1;

    EXPECT_THROW(write_mandelbrot_image_data("does-not-exist-dir/matrix.txt", pixels, options),
                 std::runtime_error);
}

TEST(PlottingAppSuite, WriteMandelbrotImageDataSupportsSinglePixelGrid)
{
    const std::string path = "test_mandelbrot_single_pixel.txt";
    const std::vector<int> pixels{7};
    PlotOptions options;
    options.width = 1;
    options.height = 1;
    options.x_min = 0.0;
    options.x_max = 1.0;
    options.y_min = 0.0;
    options.y_max = 1.0;

    write_mandelbrot_image_data(path, pixels, options);
    const std::string content = read_file(path);
    EXPECT_NE(content.find("0 0 7"), std::string::npos);
    std::remove(path.c_str());
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

TEST(PlottingAppSuite, RunPlottingAppMandelbrotCreatesAndCleansFile)
{
    PlotOptions options;
    options.mandelbrot_mode = true;
    options.width = 16;
    options.height = 12;
    options.max_iterations = 40;
    options.temp_file = "test_run_mandelbrot.txt";
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

TEST(PlottingAppSuite, RunPlottingAppInvokesGnuplotForSampledDataWhenRequested)
{
    PlotOptions options;
    options.intervals = 4;
    options.interval_size = 1.0;
    options.temp_file = "test_run_plotting_gnuplot.txt";
    options.invoke_gnuplot = true;

    setenv("PLOTTING_APP_GNUPLOT_COMMAND", "cat >/dev/null", 1);
    setenv("PLOTTING_APP_SKIP_GNUPLOT_PAUSE", "1", 1);
    unsetenv("PLOTTING_APP_NO_GNUPLOT");
    EXPECT_EQ(run_plotting_app(options), 0);
    unsetenv("PLOTTING_APP_GNUPLOT_COMMAND");
    unsetenv("PLOTTING_APP_SKIP_GNUPLOT_PAUSE");

    std::ifstream in(options.temp_file);
    EXPECT_FALSE(in.good()) << "temp file should be removed after run";
}

TEST(PlottingAppSuite, RunPlottingAppInvokesGnuplotForMandelbrotWhenRequested)
{
    PlotOptions options;
    options.mandelbrot_mode = true;
    options.width = 16;
    options.height = 12;
    options.max_iterations = 40;
    options.temp_file = "test_run_mandelbrot_gnuplot.txt";
    options.invoke_gnuplot = true;

    setenv("PLOTTING_APP_GNUPLOT_COMMAND", "cat >/dev/null", 1);
    setenv("PLOTTING_APP_SKIP_GNUPLOT_PAUSE", "1", 1);
    unsetenv("PLOTTING_APP_NO_GNUPLOT");
    EXPECT_EQ(run_plotting_app(options), 0);
    unsetenv("PLOTTING_APP_GNUPLOT_COMMAND");
    unsetenv("PLOTTING_APP_SKIP_GNUPLOT_PAUSE");

    std::ifstream in(options.temp_file);
    EXPECT_FALSE(in.good()) << "temp file should be removed after run";
}
