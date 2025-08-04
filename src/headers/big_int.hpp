#include <algorithm>
#include <cctype>
#include <cmath>
#include <compare>
#include <cstdint>
#include <execution>
#include <numeric>
#include <ranges>
#include <string>
#include <string_view>
#include <vector>
using namespace std;
using namespace std::views;
namespace views = std::views;

class BigInteger {
private:
  vector<uint32_t> digits;
  bool is_positive = true;
  static constexpr array<uint32_t, 8> powers_10 = {
      1, 10, 100, 1'000, 10'000, 100'000, 1'000'000, 10'000'000};
  // Construtor
public:
  BigInteger(string_view numerical_str) {
    auto char_to_number = [](char character) { return character - '0'; };

    auto chunks = views::reverse(numerical_str) |
                  views::transform(char_to_number) | chunk(8);
    digits.resize(chunks.size());

    auto func_chunk_to_digit = [&](auto characters) {
      return inner_product(characters.begin(), characters.end(),
                           powers_10.begin(), 0);
    };

    std::transform(chunks.begin(), chunks.end(), digits.begin(),
                   func_chunk_to_digit);
  }
  friend BigInteger operator""_bigint(const char *raw_number);

  // Igualdade
  bool operator==(const BigInteger &other) const {
    return is_positive == other.is_positive and digits == other.digits;
  }

  // Comparações
  strong_ordering operator<=>(const BigInteger &other) const {
    // Compara sinais
    if (is_positive != other.is_positive)
      return is_positive ? std::strong_ordering::greater
                         : std::strong_ordering::less;

    // Compara número de digitos
    if (digits.size() != other.digits.size())
      return (digits.size() > other.digits.size()) == is_positive
                 ? std::strong_ordering::greater
                 : std::strong_ordering::less;

    // Compara digito a digito do mais significante ao menos
    for (auto [digit_a, digit_b] : views::reverse(zip(digits, other.digits))) {
      if (digit_a != digit_b)
        return (digit_a > digit_b) == is_positive
                   ? std::strong_ordering::greater
                   : std::strong_ordering::less;
    }

    // Números são iguais
    return std::strong_ordering::equal;
  }

  BigInteger operator-() const {
    BigInteger new_number = *this;
    new_number.is_positive = !is_positive;
    return new_number;
  }

  BigInteger operator+() const { return *this; }

  vector<uint32_t> const &get_digits() const { return digits; }
};

BigInteger operator""_bigint(const char *raw_number) {
  return BigInteger(raw_number);
}

