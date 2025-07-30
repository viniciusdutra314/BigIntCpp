#include <cctype>
#include <cmath>
#include <cstdint>
#include <ranges>
#include <string_view>
#include <vector>
using namespace std;
using namespace std::views;

class BigInteger {
private:
  vector<uint32_t> digits;
  bool is_positive;

  BigInteger(const string_view numerical_str) {
    is_positive=true;
    auto is_numerical = [](char c) { return isdigit(c); };
    // get the least significant digits first
    auto reverse_numerical_str =reverse(numerical_str) | filter(is_numerical);

    // divides into chuncks of 9 numbers
    auto chuncked_digits = reverse_numerical_str | chunk(9);
    for (auto chunck : chuncked_digits) {
      uint32_t digit = 0;
      for (auto [potencia, number_char] : enumerate(chunck)) {
        digit += pow(10, potencia) * (number_char-'0');
      }
      digits.push_back(digit);
    }
  }
  friend BigInteger operator""_bigint(const char *raw_number);
public:
  //Comparações
  bool operator==(const BigInteger& other) const {
    return is_positive == other.is_positive and digits == other.digits;
  }



  BigInteger operator-() const {
    BigInteger new_number = *this;
    new_number.is_positive = false;
    return new_number;
  }

  BigInteger operator+() const {
    return *this;
  }


  vector<uint32_t> const &get_digits() const { return digits; }
};

BigInteger operator""_bigint(const char *raw_number) {
  return BigInteger(raw_number);
}