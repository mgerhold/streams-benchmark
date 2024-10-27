#include <benchmark/benchmark.h>
#include <array>
#include <charconv>
#include <cstdio>
#include <format>
#include <limits>
#include <sstream>
#include <string>
#include <vector>

template<std::size_t count>
[[nodiscard]] static consteval auto create_letters() {
    auto result = std::array<char, count>{};
    for (auto letter = 'a'; auto& current : result) {
        current = letter;
        ++letter;
        if (letter > 'z') {
            letter = 'a';
        }
    }
    return result;
}

template<std::size_t count>
[[nodiscard]] static consteval auto create_numbers() {
    auto result = std::array<double, count>{};
    for (auto x = 0.1; auto& current : result) {
        current = x;
        x += 0.1;
    }
    return result;
}

static void BM_Array(benchmark::State& state) {
    static constexpr auto size = 4;
    for (auto _ : state) {
        auto array = std::array<char, size>{};
        array[0] = 'a';
        array[1] = 'b';
        array[2] = 'c';
        array[3] = 'd';
        benchmark::DoNotOptimize(array);
    }
}

static void BM_Vector(benchmark::State& state) {
    for (auto _ : state) {
        auto vector = std::vector<char>{};
        vector.push_back('a');
        vector.push_back('b');
        vector.push_back('c');
        vector.push_back('d');
        benchmark::DoNotOptimize(vector);
    }
}

static void BM_String(benchmark::State& state) {
    for (auto _ : state) {
        auto string = std::string{};
        string += 'a';
        string += 'b';
        string += 'c';
        string += 'd';
        benchmark::DoNotOptimize(string);
    }
}

static void BM_StringStream(benchmark::State& state) {
    for (auto _ : state) {
        auto stream = std::stringstream{};
        stream << 'a';
        stream << 'b';
        stream << 'c';
        stream << 'd';
        benchmark::DoNotOptimize(stream);
    }
}

static constexpr auto num_chars = std::size_t{ 1024 * 100 };

static void BM_Array_Big(benchmark::State& state) {
    static constexpr auto letters = create_letters<num_chars>();
    for (auto _ : state) {
        auto array = std::array<char, num_chars>{};
        for (auto i = std::size_t{ 0 }; i < num_chars; ++i) {
            array[i] = letters[i];
        }
        benchmark::DoNotOptimize(array);
    }
}

static void BM_Vector_Big(benchmark::State& state) {
    static constexpr auto letters = create_letters<num_chars>();
    for (auto _ : state) {
        auto vector = std::vector<char>{};
        for (auto const letter : letters) {
            vector.push_back(letter);
        }
        benchmark::DoNotOptimize(vector);
    }
}

static void BM_String_Big(benchmark::State& state) {
    static constexpr auto letters = create_letters<num_chars>();
    for (auto _ : state) {
        auto string = std::string{};
        for (auto const letter : letters) {
            string += letter;
        }
        benchmark::DoNotOptimize(string);
    }
}

static void BM_StringStream_Big(benchmark::State& state) {
    static constexpr auto letters = create_letters<num_chars>();
    for (auto _ : state) {
        auto stream = std::stringstream{};
        for (auto const letter : letters) {
            stream << letter;
        }
        benchmark::DoNotOptimize(stream);
    }
}

static constexpr auto num_doubles = std::size_t{ 1024 };

static void BM_Format_Doubles_Snprintf(benchmark::State& state) {
    static constexpr auto numbers = create_numbers<num_doubles>();
    for (auto _ : state) {
        auto array = std::array<char, std::numeric_limits<double>::max_digits10>{};
        for (auto const number : numbers) {
            std::snprintf(array.data(), array.size(), "%lf", number);
        }
        benchmark::DoNotOptimize(array);
    }
}

static void BM_Format_Doubles_To_Chars(benchmark::State& state) {
    static constexpr auto numbers = create_numbers<num_doubles>();
    for (auto _ : state) {
        auto array = std::array<char, std::numeric_limits<double>::max_digits10>{};
        for (auto const number : numbers) {
            std::to_chars(array.data(), array.data() + array.size(), number);
        }
        benchmark::DoNotOptimize(array);
    }
}

static void BM_Format_Doubles_Format_To_Vector_Back_Inserter(benchmark::State& state) {
    static constexpr auto numbers = create_numbers<num_doubles>();
    static const auto locale = std::locale{ "de_DE.UTF-8" };
    for (auto _ : state) {
        auto vector = std::vector<char>{};
        for (auto const number : numbers) {
            std::format_to(std::back_inserter(vector), locale, "{}", number);
        }
        benchmark::DoNotOptimize(vector);
    }
}

static void BM_Format_Doubles_Format_String(benchmark::State& state) {
    static constexpr auto numbers = create_numbers<num_doubles>();
    static const auto locale = std::locale{ "de_DE.UTF-8" };
    for (auto _ : state) {
        auto string = std::string{};
        for (auto const number : numbers) {
            string += std::format(locale, "{}", number);
        }
        benchmark::DoNotOptimize(string);
    }
}

static void BM_Format_Doubles_String_Stream(benchmark::State& state) {
    static constexpr auto numbers = create_numbers<num_doubles>();
    static const auto locale = std::locale{ "de_DE.UTF-8" };
    for (auto _ : state) {
        auto stream = std::stringstream{};
        stream.imbue(locale);
        for (auto const number : numbers) {
            stream << number;
        }
        benchmark::DoNotOptimize(stream);
    }
}

BENCHMARK(BM_Array);
BENCHMARK(BM_Vector);
BENCHMARK(BM_String);
BENCHMARK(BM_StringStream);
BENCHMARK(BM_Array_Big);
BENCHMARK(BM_Vector_Big);
BENCHMARK(BM_String_Big);
BENCHMARK(BM_StringStream_Big);

BENCHMARK(BM_Format_Doubles_Snprintf);
BENCHMARK(BM_Format_Doubles_To_Chars);
BENCHMARK(BM_Format_Doubles_Format_To_Vector_Back_Inserter);
BENCHMARK(BM_Format_Doubles_Format_String);
BENCHMARK(BM_Format_Doubles_String_Stream);

BENCHMARK_MAIN();
