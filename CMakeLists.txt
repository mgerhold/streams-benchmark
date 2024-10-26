cmake_minimum_required(VERSION 3.27)
project(streams_benchmark)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

include(dependencies.cmake)
streams_benchmark_setup_dependencies()

include(project_options.cmake)

add_subdirectory(src bin)

#if (${streams_benchmark_build_tests})
#    enable_testing()
#    add_subdirectory(test)
#endif ()
