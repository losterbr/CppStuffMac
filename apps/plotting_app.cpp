#include "plotting_app.hpp"

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <memory>
#include <string>
#include <stdexcept>

#include "mandelbrot.hpp"

namespace
{
using PipeHandle = std::unique_ptr<FILE, int (*)(FILE *)>;

std::string gnuplot_command()
{
    const char *command = std::getenv("PLOTTING_APP_GNUPLOT_COMMAND");
    if (command != nullptr && command[0] != '\0')
    {
        return command;
    }
    return "gnuplot -persist";
}

PipeHandle open_gnuplot_pipe()
{
    return PipeHandle(popen(gnuplot_command().c_str(), "w"), pclose);
}

void write_gnuplot_header(FILE *pipe, const std::string &title, const std::string &xlabel,
                          const std::string &ylabel)
{
    std::fprintf(pipe, "set term qt font \"Helvetica,10\"\n");
    std::fprintf(pipe, "set title \"%s\"\n", title.c_str());
    std::fprintf(pipe, "set xlabel \"%s\"\n", xlabel.c_str());
    std::fprintf(pipe, "set ylabel \"%s\"\n", ylabel.c_str());
    std::fprintf(pipe, "set mouse\n");
}

void write_gnuplot_pause(FILE *pipe)
{
    const char *skip_pause = std::getenv("PLOTTING_APP_SKIP_GNUPLOT_PAUSE");
    if (!(skip_pause != nullptr && skip_pause[0] != '\0'))
    {
        std::fprintf(pipe, "pause mouse close\n");
    }
}

bool try_plot_with_gnuplot(const std::string &file_path, double x_min, double x_max)
{
    PipeHandle gnuplot_pipe = open_gnuplot_pipe();
    if (!gnuplot_pipe)
    {
        return false;
    }

    write_gnuplot_header(gnuplot_pipe.get(), "Sampled function plot", "x", "y");
    std::fprintf(gnuplot_pipe.get(), "set key top right\n");
    std::fprintf(gnuplot_pipe.get(), "f(x)=sin(x)*cos(10*x)\n");
    std::fprintf(gnuplot_pipe.get(),
                 "plot [%g:%g] \"%s\" with lines title \"sampled data\", f(x) with lines lw 2 "
                 "title \"f(x)=sin(x)*cos(10*x)\"\n",
                 x_min, x_max, file_path.c_str());
    write_gnuplot_pause(gnuplot_pipe.get());
    return true;
}

bool try_plot_mandelbrot_with_gnuplot(const PlotOptions &options)
{
    PipeHandle gnuplot_pipe = open_gnuplot_pipe();
    if (!gnuplot_pipe)
    {
        return false;
    }

    write_gnuplot_header(gnuplot_pipe.get(), "Mandelbrot set", "Re(c)", "Im(c)");
    std::fprintf(gnuplot_pipe.get(), "unset key\n");
    std::fprintf(gnuplot_pipe.get(), "set size ratio -1\n");
    std::fprintf(gnuplot_pipe.get(), "set view map\n");
    std::fprintf(gnuplot_pipe.get(), "set xrange [%g:%g]\n", options.x_min, options.x_max);
    std::fprintf(gnuplot_pipe.get(), "set yrange [%g:%g]\n", options.y_min, options.y_max);
    std::fprintf(gnuplot_pipe.get(), "set palette rgbformulae 33,13,10\n");
    std::fprintf(gnuplot_pipe.get(), "plot \"%s\" using 1:2:3 with image\n",
                 options.temp_file.c_str());
    write_gnuplot_pause(gnuplot_pipe.get());
    return true;
}

bool should_invoke_gnuplot(bool requested)
{
    if (!requested)
    {
        return false;
    }

    const char *disable_plot = std::getenv("PLOTTING_APP_NO_GNUPLOT");
    return disable_plot == nullptr || disable_plot[0] == '\0';
}
} // namespace

std::vector<double> build_x_data(int intervals, double interval_size)
{
    if (intervals <= 0)
    {
        throw std::invalid_argument("intervals must be positive");
    }
    if (interval_size <= 0.0)
    {
        throw std::invalid_argument("interval_size must be positive");
    }

    const double step_size = interval_size / static_cast<double>(intervals);
    std::vector<double> x_data(static_cast<size_t>(intervals) + 1U, 0.0);
    for (int i = 0; i < intervals; ++i)
    {
        x_data[static_cast<size_t>(i + 1)] = x_data[static_cast<size_t>(i)] + step_size;
    }
    return x_data;
}

std::vector<double> build_y_data(const std::vector<double> &x_data)
{
    std::vector<double> y_data;
    y_data.reserve(x_data.size());
    for (double x : x_data)
    {
        y_data.push_back(std::sin(x) * std::cos(10.0 * x));
    }
    return y_data;
}

void write_plot_data(const std::string &file_path, const std::vector<double> &x_data,
                     const std::vector<double> &y_data)
{
    if (x_data.size() != y_data.size())
    {
        throw std::invalid_argument("x_data and y_data must have the same size");
    }

    std::ofstream output(file_path);
    if (!output)
    {
        throw std::runtime_error("failed to open output file");
    }

    for (size_t i = 0; i < x_data.size(); ++i)
    {
        output << x_data[i] << ' ' << y_data[i] << '\n';
    }
}

std::vector<int> build_mandelbrot_image(const PlotOptions &options)
{
    if (options.width <= 0 || options.height <= 0)
    {
        throw std::invalid_argument("width and height must be positive");
    }
    if (options.max_iterations <= 0)
    {
        throw std::invalid_argument("max_iterations must be positive");
    }
    if (options.x_min >= options.x_max || options.y_min >= options.y_max)
    {
        throw std::invalid_argument("invalid plot bounds");
    }

    const int width = options.width;
    const int height = options.height;
    const double x_range = options.x_max - options.x_min;
    const double y_range = options.y_max - options.y_min;

    Mandelbrot set(options.max_iterations, true);
    std::vector<int> pixels(static_cast<size_t>(width) * static_cast<size_t>(height), 0);

    for (int row = 0; row < height; ++row)
    {
        const double y = (height == 1) ? options.y_min
                                       : options.y_max - (static_cast<double>(row) * y_range) /
                                                             static_cast<double>(height - 1);
        for (int col = 0; col < width; ++col)
        {
            const double x = (width == 1) ? options.x_min
                                          : options.x_min + (static_cast<double>(col) * x_range) /
                                                                static_cast<double>(width - 1);
            const int iters = set.iterations(Complex(x, y));
            const size_t index =
                static_cast<size_t>(row) * static_cast<size_t>(width) + static_cast<size_t>(col);
            pixels[index] = (iters < 0) ? (options.max_iterations + 1) : iters;
        }
    }

    return pixels;
}

void write_mandelbrot_image_data(const std::string &file_path, const std::vector<int> &pixels,
                                 const PlotOptions &options)
{
    const int width = options.width;
    const int height = options.height;

    if (width <= 0 || height <= 0)
    {
        throw std::invalid_argument("width and height must be positive");
    }
    if (options.x_min >= options.x_max || options.y_min >= options.y_max)
    {
        throw std::invalid_argument("invalid plot bounds");
    }
    if (pixels.size() != static_cast<size_t>(width) * static_cast<size_t>(height))
    {
        throw std::invalid_argument("pixels size does not match width*height");
    }

    std::ofstream output(file_path);
    if (!output)
    {
        throw std::runtime_error("failed to open output file");
    }

    const double x_range = options.x_max - options.x_min;
    const double y_range = options.y_max - options.y_min;

    for (int row = 0; row < height; ++row)
    {
        const double y = (height == 1) ? options.y_min
                                       : options.y_max - (static_cast<double>(row) * y_range) /
                                                             static_cast<double>(height - 1);
        for (int col = 0; col < width; ++col)
        {
            const double x = (width == 1) ? options.x_min
                                          : options.x_min + (static_cast<double>(col) * x_range) /
                                                                static_cast<double>(width - 1);
            const size_t index =
                static_cast<size_t>(row) * static_cast<size_t>(width) + static_cast<size_t>(col);
            output << x << ' ' << y << ' ' << pixels[index] << '\n';
        }
        output << '\n';
    }
}

int run_plotting_app(const PlotOptions &options)
{
    if (options.mandelbrot_mode)
    {
        const std::vector<int> pixels = build_mandelbrot_image(options);
        write_mandelbrot_image_data(options.temp_file, pixels, options);

        if (should_invoke_gnuplot(options.invoke_gnuplot))
        {
            (void)try_plot_mandelbrot_with_gnuplot(options);
        }

        std::remove(options.temp_file.c_str());
        return 0;
    }

    const std::vector<double> x_data = build_x_data(options.intervals, options.interval_size);
    const std::vector<double> y_data = build_y_data(x_data);
    write_plot_data(options.temp_file, x_data, y_data);

    if (should_invoke_gnuplot(options.invoke_gnuplot))
    {
        (void)try_plot_with_gnuplot(options.temp_file, x_data.front(), x_data.back());
    }

    std::remove(options.temp_file.c_str());
    return 0;
}
