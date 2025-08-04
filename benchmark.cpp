#include <cctype>
#include <cmath>
#include <compare>
#include <cstdint>
#include <ranges>
#include <string>
#include <string_view>
#include <vector>
#include <chrono>

using namespace std;
using namespace std::views;


string generate_numeric_string(size_t length) {
    string s;
    s.reserve(length);
    for (size_t i = 0; i < length; ++i)
        s += '0' + (i % 10);
    return s;
}

static void CParser(benchmark::State& state){
    auto cpp_str=generate_numeric_string(10'000);
    char const* text_begin=cpp_str.c_str();
    size_t N=cpp_str.length();
    char const * end_ptr=text_begin + N;
    for (auto _ : state){
      uint32_t num_elements=ceil(N/8.0f);
      uint32_t* digits_vec=(uint32_t*) malloc(sizeof(uint32_t)*num_elements);
      char const * current_char_ptr=end_ptr;
      uint32_t exp_counter=0,digit_counter=0,digit=0;
      while (current_char_ptr!=text_begin){
          current_char_ptr--;
          digit+=(uint32_t)(pow(10, exp_counter) * (*current_char_ptr - '0'));
          exp_counter++;
          if (exp_counter==8){
            *(digits_vec+digit_counter)=digit;
            digit_counter++;
            exp_counter=0;
          }
      }
      if (exp_counter > 0){
          digits_vec[digit_counter++] = digit;
      }
      free(digits_vec);
    }
}

BENCHMARK(CParser);


static void CppParser(benchmark::State& state){
  auto numerical_str=generate_numeric_string(10'000);
  size_t num_elements=ceil(numerical_str.length()/8.0f);
  for (auto _ : state){
    vector<uint32_t> digits(num_elements);
    for (auto&& [digit,numbers_chunk] : zip(digits,numerical_str | views::reverse | chunk(8))) {
      digit=0;
      for (auto [exponent,character] : enumerate(numbers_chunk))
        digit+=pow(10,exponent)*(character-'0');
    }
  }
  
}

BENCHMARK(CppParser);
