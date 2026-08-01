cmake_minimum_required(VERSION 3.21)
project(CppStuffMac VERSION 0.2.0 LANGUAGES CXX)

if(APPLE)
  execute_process(
    COMMAND xcrun --sdk macosx --show-sdk-path
    OUTPUT_VARIABLE CMAKE_OSX_SYSROOT
    OUTPUT_STRIP_TRAILING_WHITESPACE
  )
endif()

include(CTest)
enable_testing()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(CPPSTUFFMAC_ENABLE_WARNINGS "Enable strict compiler warnings" ON)

function(enable_project_warnings target_name)
  if(NOT CPPSTUFFMAC_ENABLE_WARNINGS)
    return()
  endif()

  if(MSVC)
    target_compile_options(${target_name} PRIVATE /W4)
  else()
    target_compile_options(${target_name} PRIVATE
      -Wall
      -Wextra
      -Wpedantic
      -Wno-unused-parameter
      -Wno-unused-variable
    )
  endif()
endfunction()

add_library(complexnumbers ./source/complexnumbers.cpp)
target_include_directories(complexnumbers PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_compile_features(complexnumbers PUBLIC cxx_std_20)

add_library(mandelbrot ./source/mandelbrot.cpp)
target_include_directories(mandelbrot PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(mandelbrot PUBLIC complexnumbers)
target_compile_features(mandelbrot PUBLIC cxx_std_20)

add_library(terminalcolour ./source/terminalcolour.cpp)
target_include_directories(terminalcolour PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_compile_features(terminalcolour PUBLIC cxx_std_20)

add_executable(Main ./source/main.cpp)
target_link_libraries(Main PRIVATE mandelbrot terminalcolour)
target_compile_features(Main PRIVATE cxx_std_20)

add_executable(Plotting ./source/plotting.cpp)
target_compile_features(Plotting PRIVATE cxx_std_20)

enable_project_warnings(complexnumbers)
enable_project_warnings(mandelbrot)
enable_project_warnings(terminalcolour)
enable_project_warnings(Main)
enable_project_warnings(Plotting)

# GTest
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.16.0.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include(GoogleTest)

add_executable(TestComplexNumbers ./source/testcomplexnumbers.cpp)
target_link_libraries(TestComplexNumbers PRIVATE complexnumbers gtest_main)
target_compile_features(TestComplexNumbers PRIVATE cxx_std_20)

add_executable(TestMandelbrot ./source/testmandelbrot.cpp)
target_link_libraries(TestMandelbrot PRIVATE mandelbrot gtest_main)
target_compile_features(TestMandelbrot PRIVATE cxx_std_20)

enable_project_warnings(TestComplexNumbers)
enable_project_warnings(TestMandelbrot)

gtest_discover_tests(TestComplexNumbers)
gtest_discover_tests(TestMandelbrot)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)