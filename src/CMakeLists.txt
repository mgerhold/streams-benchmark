add_executable(streams_benchmark main.cpp)

target_link_libraries(
        streams_benchmark
        PRIVATE
        streams_benchmark_project_options
)

target_link_system_libraries(
        streams_benchmark
        PRIVATE
        benchmark::benchmark
)
