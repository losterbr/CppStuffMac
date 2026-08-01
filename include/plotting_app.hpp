#pragma once

#include <string>
#include <vector>

struct PlotOptions
{
    int intervals = 100;
    double interval_size = 1.0;
    std::string temp_file = "tempData";
    bool invoke_gnuplot = true;
};

std::vector<double> build_x_data(int intervals, double interval_size);
std::vector<double> build_y_data(const std::vector<double> &x_data);
void write_plot_data(const std::string &file_path, const std::vector<double> &x_data,
                     const std::vector<double> &y_data);
int run_plotting_app(const PlotOptions &options = PlotOptions{});
