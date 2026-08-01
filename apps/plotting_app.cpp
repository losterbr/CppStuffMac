#include "plotting_app.hpp"

#include <cmath>
#include <cstdio>
#include <fstream>
#include <stdexcept>

namespace
{
bool try_plot_with_gnuplot(const std::string &file_path)
{
    FILE *gnuplot_pipe = popen("gnuplot", "w");
    if (gnuplot_pipe == nullptr)
    {
        return false;
    }

    std::fprintf(gnuplot_pipe, "plot \"%s\" with lines\n", file_path.c_str());
    std::fprintf(gnuplot_pipe, "exit\n");
    pclose(gnuplot_pipe);
    return true;
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

int run_plotting_app(const PlotOptions &options)
{
    const std::vector<double> x_data = build_x_data(options.intervals, options.interval_size);
    const std::vector<double> y_data = build_y_data(x_data);
    write_plot_data(options.temp_file, x_data, y_data);

    if (options.invoke_gnuplot)
    {
        (void)try_plot_with_gnuplot(options.temp_file);
    }

    std::remove(options.temp_file.c_str());
    return 0;
}
