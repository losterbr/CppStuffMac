#include <iostream>
#include <string_view>

#include "main_app.hpp"

int main(int argc, char **argv)
{
	if (argc > 1 && std::string_view(argv[1]) == "--non-interactive")
	{
		return run_main_app_noninteractive(std::cout);
	}

	return run_main_app_interactive(std::cin, std::cout);
}