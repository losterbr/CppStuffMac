#pragma once

#include <iosfwd>

int run_main_app_noninteractive(std::ostream &os);
int run_main_app_interactive(std::istream &is, std::ostream &os);
