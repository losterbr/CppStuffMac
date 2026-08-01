add_library(mainapplogic main_app.cpp)
target_include_directories(mainapplogic PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(mainapplogic PUBLIC mandelbrot terminalcolour)
cppstuffmac_enable_warnings(mainapplogic)

add_library(plottingapplogic plotting_app.cpp)
target_include_directories(plottingapplogic PUBLIC ${PROJECT_SOURCE_DIR}/include)
cppstuffmac_enable_warnings(plottingapplogic)

add_executable(Main main.cpp)
target_link_libraries(Main PRIVATE mainapplogic)
cppstuffmac_enable_warnings(Main)

add_executable(Plotting plotting.cpp)
target_link_libraries(Plotting PRIVATE plottingapplogic)
cppstuffmac_enable_warnings(Plotting)

if(BUILD_TESTING)
  add_test(NAME RunMain COMMAND Main --non-interactive)
  add_test(NAME RunPlotting COMMAND Plotting)
  set_tests_properties(RunPlotting PROPERTIES ENVIRONMENT "PLOTTING_APP_NO_GNUPLOT=1")
endif()
