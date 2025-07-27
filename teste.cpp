#include <algorithm>
#include <concepts>
#include <limits>
#include <numeric>
#include <print>
#include <ranges>
#include <stdexcept>
#include <cstdint>
#include <concepts>
#include <format>
using namespace std;
namespace views=std::views;
namespace ranges =std::ranges;



template<unsigned_integral Number>
Number safe_add(Number x,Number y){
    Number biggest_value=numeric_limits<Number>::max();
    if (x>biggest_value-y){
        throw overflow_error(format("Overflow happend, numerical_limit is {}<{}+{}",
            biggest_value, x, y));
    }
    return x+y;
}

template<unsigned_integral Number>
Number safe_multiply(Number x,Number y){
    Number biggest_value=numeric_limits<Number>::max();
    if (x>biggest_value/y){
        throw overflow_error(format("Overflow happend, numerical_limit is {}<{}*{}",
            biggest_value, x, y));
    }
    return x*y;
}

template<unsigned_integral Number>
Number factorial(Number n){
    Number result=1;
    while (n!=0) {
        result=safe_multiply(result,n);
        n--;
    }
    return result;
}





int main(){
    auto x=views::iota(uint8_t{0},uint8_t{10});
    for (auto v :x){
        println("{}! = {}",v,factorial(v));
    }

}