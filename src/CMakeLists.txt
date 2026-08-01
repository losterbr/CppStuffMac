add_library(complexnumbers complexnumbers.cpp)
target_include_directories(complexnumbers PUBLIC ${PROJECT_SOURCE_DIR}/include)
cppstuffmac_enable_warnings(complexnumbers)

add_library(mandelbrot mandelbrot.cpp)
target_include_directories(mandelbrot PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(mandelbrot PUBLIC complexnumbers)
cppstuffmac_enable_warnings(mandelbrot)

add_library(terminalcolour terminalcolour.cpp)
target_include_directories(terminalcolour PUBLIC ${PROJECT_SOURCE_DIR}/include)
cppstuffmac_enable_warnings(terminalcolour)
