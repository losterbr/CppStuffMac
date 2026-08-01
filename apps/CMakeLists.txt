add_executable(Main main.cpp)
target_link_libraries(Main PRIVATE mandelbrot terminalcolour)
target_compile_features(Main PRIVATE cxx_std_20)
cppstuffmac_enable_warnings(Main)

add_executable(Plotting plotting.cpp)
target_compile_features(Plotting PRIVATE cxx_std_20)
cppstuffmac_enable_warnings(Plotting)
