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

include(${PROJECT_SOURCE_DIR}/cmake/CompilerWarnings.cmake)

add_subdirectory(${PROJECT_SOURCE_DIR}/src)
add_subdirectory(${PROJECT_SOURCE_DIR}/apps)

if(BUILD_TESTING)
  add_subdirectory(${PROJECT_SOURCE_DIR}/tests)
endif()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)