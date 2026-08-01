include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.16.0.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include(GoogleTest)

add_executable(TestComplexNumbers unit/test_complexnumbers.cpp)
target_link_libraries(TestComplexNumbers PRIVATE complexnumbers gtest_main)
target_compile_features(TestComplexNumbers PRIVATE cxx_std_20)
cppstuffmac_enable_warnings(TestComplexNumbers)

gtest_discover_tests(TestComplexNumbers)

add_executable(TestMandelbrot unit/test_mandelbrot.cpp)
target_link_libraries(TestMandelbrot PRIVATE mandelbrot gtest_main)
target_compile_features(TestMandelbrot PRIVATE cxx_std_20)
cppstuffmac_enable_warnings(TestMandelbrot)

gtest_discover_tests(TestMandelbrot)

add_executable(TestApps unit/test_apps.cpp)
target_link_libraries(TestApps PRIVATE mainapplogic plottingapplogic gtest_main)
target_compile_features(TestApps PRIVATE cxx_std_20)
cppstuffmac_enable_warnings(TestApps)

gtest_discover_tests(TestApps)
