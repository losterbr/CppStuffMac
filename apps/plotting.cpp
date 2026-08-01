#include "plotting_app.hpp"

#include <string_view>

int main(int argc, char **argv)
{
    PlotOptions options;
    options.invoke_gnuplot = false;

    if (argc > 1 && std::string_view(argv[1]) == "--gnuplot")
    {
        options.invoke_gnuplot = true;
    }

    return run_plotting_app(options);
}