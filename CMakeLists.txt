cmake_minimum_required(VERSION 3.14)
project(MyProject VERSION 0.1.0)
# TODO: Clean-up
include(CTest)
enable_testing()

add_executable(Main main.cpp)
add_executable(Plotting plotting.cpp)

add_executable(TestComplexNumbers testcomplexnumbers.cpp)
add_executable(TestMandelbrot testmandelbrot.cpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

target_compile_features(TestMandelbrot PRIVATE cxx_std_17)
target_compile_features(Main PRIVATE cxx_std_17)
target_compile_features(Plotting PRIVATE cxx_std_17)

# GTest
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
target_link_libraries(TestComplexNumbers gtest_main)
target_link_libraries(TestMandelbrot gtest_main)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

set(CMAKE_CXX_FLAGS "-Wno-unused-variable -Wno-unused-parameter -Wall")

add_test(NAME TestComplexNumbers COMMAND TestComplexNumbers)
add_test(NAME TestMandelbrot COMMAND TestMandelbrot)