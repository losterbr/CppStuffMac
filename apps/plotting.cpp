#include "plotting_app.hpp"

#include <iostream>
#include <string>
#include <string_view>

int main(int argc, char **argv)
{
    PlotOptions options;
    options.invoke_gnuplot = false;

    for (int i = 1; i < argc; ++i)
    {
        const std::string_view arg(argv[i]);
        if (arg == "--gnuplot")
        {
            options.invoke_gnuplot = true;
            continue;
        }
        if (arg == "--mandelbrot")
        {
            options.mandelbrot_mode = true;
            continue;
        }
        if (arg == "--width" && i + 1 < argc)
        {
            options.width = std::stoi(argv[++i]);
            continue;
        }
        if (arg == "--height" && i + 1 < argc)
        {
            options.height = std::stoi(argv[++i]);
            continue;
        }
        if (arg == "--max-iterations" && i + 1 < argc)
        {
            options.max_iterations = std::stoi(argv[++i]);
            continue;
        }
        if (arg == "--xmin" && i + 1 < argc)
        {
            options.x_min = std::stod(argv[++i]);
            continue;
        }
        if (arg == "--xmax" && i + 1 < argc)
        {
            options.x_max = std::stod(argv[++i]);
            continue;
        }
        if (arg == "--ymin" && i + 1 < argc)
        {
            options.y_min = std::stod(argv[++i]);
            continue;
        }
        if (arg == "--ymax" && i + 1 < argc)
        {
            options.y_max = std::stod(argv[++i]);
            continue;
        }

        std::cerr << "Unknown or incomplete option: " << arg << '\n';
        return 1;
    }

    return run_plotting_app(options);
}