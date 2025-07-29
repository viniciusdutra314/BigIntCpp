#include "big_int.hpp"
#include <print>

int main(){
    BigInteger number("5313");
    auto& digits=number.get_digits();
    for (auto& digit: views::reverse(digits)){
        println("{}",digit);
    }
}