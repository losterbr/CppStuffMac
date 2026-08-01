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

set(CPPSTUFFMAC_CXX_STANDARD 20)
if("cxx_std_23" IN_LIST CMAKE_CXX_COMPILE_FEATURES)
  set(CPPSTUFFMAC_CXX_STANDARD 23)
endif()

set(CMAKE_CXX_STANDARD ${CPPSTUFFMAC_CXX_STANDARD})
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

message(STATUS "CppStuffMac C++ standard: C++${CMAKE_CXX_STANDARD}")

# Keep build outputs grouped in predictable folders.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

option(CPPSTUFFMAC_ENABLE_WARNINGS "Enable strict compiler warnings" ON)
option(CPPSTUFFMAC_ENABLE_COVERAGE "Enable coverage instrumentation flags" OFF)

if(CPPSTUFFMAC_ENABLE_COVERAGE)
  if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
    add_compile_options(-O0 -g --coverage)
    add_link_options(--coverage)
  else()
    message(WARNING "Coverage is enabled but unsupported for compiler: ${CMAKE_CXX_COMPILER_ID}")
  endif()
endif()

include(${PROJECT_SOURCE_DIR}/cmake/CompilerWarnings.cmake)

add_subdirectory(${PROJECT_SOURCE_DIR}/src)
add_subdirectory(${PROJECT_SOURCE_DIR}/apps)

if(BUILD_TESTING)
  add_subdirectory(${PROJECT_SOURCE_DIR}/tests)
endif()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)