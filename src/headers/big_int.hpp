#include <cctype>
#include <cmath>
#include <compare>
#include <cstdint>
#include <ranges>
#include <string>
#include <string_view>
#include <vector>
using namespace std;
using namespace std::views;
namespace views =std::views;

class BigInteger {
private:
  vector<uint32_t> digits;
  bool is_positive;

  //Construtor
  BigInteger(const string_view numerical_str) {
    is_positive = true;
    auto is_numerical = [](char c) { return isdigit(c); };
    for (auto chunck_8_digits :
         views::reverse(numerical_str) | filter(is_numerical) | chunk(8)) {
      digits.push_back(stol(to<string>(chunck_8_digits)));
    }
  }
  friend BigInteger operator""_bigint(const char *raw_number);

public:
  //Igualdade
  bool operator==(const BigInteger &other) const{
    return is_positive==other.is_positive and digits==other.digits;
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
        return (digit_a > digit_b) == is_positive ? std::strong_ordering::greater
                                      : std::strong_ordering::less;
    }

    // Números são iguais
    return std::strong_ordering::equal;
  }

  BigInteger operator-() const {
    BigInteger new_number = *this;
    new_number.is_positive = false;
    return new_number;
  }

  BigInteger operator+() const { return *this; }

  vector<uint32_t> const &get_digits() const { return digits; }
};

BigInteger operator""_bigint(const char *raw_number) {
  return BigInteger(raw_number);
}