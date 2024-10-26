include("${CMAKE_SOURCE_DIR}/cmake/CPM.cmake")
include("${CMAKE_SOURCE_DIR}/cmake/system_link.cmake")

function(streams_benchmark_setup_dependencies)
    CPMAddPackage(
            NAME GOOGLE_BENCHMARK
            GITHUB_REPOSITORY google/benchmark
            VERSION 1.9.0
            OPTIONS
            "BENCHMARK_ENABLE_TESTING OFF"
    )
endfunction()
