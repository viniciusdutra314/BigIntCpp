#include <cassert>
#include <cctype>
#include <cmath>
#include <compare>
#include <cstdint>
#include <ranges>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>
#include <chrono>
#include <benchmark/benchmark.h>
#include "big_int.hpp"

using namespace std;
using namespace std::views;

uint32_t *c_bigint_parser(string const &numerical_str) {
  char const *text_begin = numerical_str.c_str();
  size_t N = numerical_str.length();
  char const *end_ptr = text_begin + N;
  uint32_t num_elements = ceil(N / 8.0f);
  uint32_t *digits_vec = (uint32_t *)malloc(sizeof(uint32_t) * num_elements);
  uint32_t powers_10[]= {1, 10, 100, 1'000, 10'000, 100'000, 1'000'000, 10'000'000};
  char const *current_char_ptr = end_ptr;
  uint32_t exp_counter = 0, digit_counter = 0, digit = 0;
  while (current_char_ptr != text_begin) {
    current_char_ptr--;
    digit += powers_10[exp_counter] * (*current_char_ptr - '0');
    exp_counter++;
    if (exp_counter == 8) {
      *(digits_vec + digit_counter) = digit;
      digit=0;
      digit_counter++;
      exp_counter = 0;
    }
  }
  if (exp_counter > 0) {
    digits_vec[digit_counter++] = digit;
  }
  return digits_vec;
}

string generate_numeric_string(size_t length) {
    string s;
    s.reserve(length);
    for (size_t i = 0; i < length; ++i)
        s += '0' + (i % 10);
    return s;
}

static void CParser(benchmark::State& state){
    auto numerical_str=generate_numeric_string(1'000'000);
    
    for (auto _ :state){
      auto c_vec=c_bigint_parser(numerical_str);
      state.PauseTiming();
      BigInteger x(numerical_str);
      auto x_vec=x.get_digits();
      bool are_equal = std::equal(x_vec.begin(), x_vec.end(), c_vec);
      if (!are_equal){
        throw std::logic_error("C implementation is incorrect");
      }
      free(c_vec);
      state.ResumeTiming();
    }

}

BENCHMARK(CParser);


static void CppParser(benchmark::State& state){
  auto numerical_str=generate_numeric_string(1'000'000);
  for (auto _ : state){
    BigInteger x(numerical_str);

  }
  
}

BENCHMARK(CppParser);
BENCHMARK_MAIN();