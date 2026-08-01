#pragma once

#include <string>
#include <vector>

struct PlotOptions
{
    int intervals = 100;
    double interval_size = 1.0;
    std::string temp_file = "/tmp/tempData";
    bool invoke_gnuplot = true;

    bool mandelbrot_mode = false;
    int width = 640;
    int height = 480;
    int max_iterations = 500;
    double x_min = -2.5;
    double x_max = 1.0;
    double y_min = -1.5;
    double y_max = 1.5;
};

std::vector<double> build_x_data(int intervals, double interval_size);
std::vector<double> build_y_data(const std::vector<double> &x_data);
void write_plot_data(const std::string &file_path, const std::vector<double> &x_data,
                     const std::vector<double> &y_data);
std::vector<int> build_mandelbrot_image(const PlotOptions &options);
void write_mandelbrot_image_data(const std::string &file_path, const std::vector<int> &pixels,
                                 const PlotOptions &options);
int run_plotting_app(const PlotOptions &options = PlotOptions{});
