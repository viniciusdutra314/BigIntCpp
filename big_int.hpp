#include <algorithm>
#include <cctype>
#include <cstdint>
#include <format>
#include <numeric>
#include <ranges>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>
using namespace std;
using namespace std::views;
using namespace std::ranges;
namespace ranges = std::ranges;
namespace views = std::ranges::views;

class BigInteger {
  vector<uint64_t> digits;
  bool is_negative;

public:
  BigInteger(const string_view numerical_str) {
    // get the least significant digits first
    auto reverse_numerical_str = views::reverse(numerical_str);

    // Remove leading spaces
    auto is_empty_space = [](char c) { return isspace(c); };
    auto trimmed_str = reverse_numerical_str | drop_while(is_empty_space);
    if (trimmed_str.empty()) {
      throw std::invalid_argument(
          "Input string is empty or only contains spaces.");
    }

    // finds the sign
    auto first_character = trimmed_str.front();
    if (first_character == '-' or first_character == '+' or
        isdigit(first_character)) {
      is_negative = (first_character == '-');
    } else {
      throw invalid_argument(
          "First non-empty character should be one of this (0-9 | + | - )");
    }

    // takes the numerical part
    auto is_numerical = [](char c) { return isdigit(c); };
    auto characters_to_jump = isdigit(first_character) ? 0 : 1;
    auto numerical_part =
        trimmed_str | drop(characters_to_jump) | take_while(is_numerical);

    // divides into chuncks
    auto chuncked_digits = numerical_part | chunk(3);
    auto chars_to_a_number = [](uint64_t accumulator, char digit) {
      return accumulator * 10 + (digit - '0');
    };
    ranges::transform(chuncked_digits, std::back_inserter(digits),
                      [chars_to_a_number](auto chunk) {
                        return ranges::fold_left(chunk, 0, chars_to_a_number);
                      });
  }
  vector<uint64_t> const &get_digits() const { return digits; }
};
