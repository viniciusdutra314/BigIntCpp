#include <concepts>
#include <limits>
#include <compare>
#include <format>
using namespace std;

template<unsigned_integral NumberType>
class SafeNumber{
    private:
        NumberType number;
        constexpr static NumberType biggest_value=numeric_limits<NumberType>::max();
        constexpr static NumberType smallest_value=numeric_limits<NumberType>::min();
    public:
        SafeNumber(NumberType x) : number(x){;};

        auto operator<=>(const SafeNumber&) const = default;

        SafeNumber operator*(SafeNumber other_number){
            if (number>biggest_value/other_number.number){
                throw overflow_error(format("Overflow happend, numerical_limit={}<{}*{}",
                    biggest_value, number, other_number.number));
            }
            return number*other_number.number; 
        }

        SafeNumber operator+(SafeNumber other_number){
            if (number>biggest_value-other_number.number){
                throw overflow_error(format("Overflow happend, numerical_limit={}<{}+{}",
                    biggest_value, number, other_number.number));
            }
            return number+other_number.number; 
        }

        SafeNumber operator-(SafeNumber other_number){
            if (other_number.number>number){
                throw overflow_error(format("Underflow happend, numerical_limit={}>{}-{}",
                smallest_value, number, other_number.number));
            }
            return other_number.number-number;
        }


};