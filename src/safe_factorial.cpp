#include "safe_number.hpp"
#include <cassert>
#include <cstdint>
#include <iostream>
#include <print>
#include <cstring>
#include <stdexcept>

template<typename Number>
Number factorial(Number n){
    Number result=1;
    while (n!=0){
        result=result*n;
        n=n-1;
    }
    return result;
}
template<typename Number>
void print_results(Number n){
    println("factorial({}) = {}",n,factorial(n));
    try {

        println("factorial(SafeNumber({})) = {} ",n,factorial(SafeNumber(n)));
    }
    catch (overflow_error error){
        println("SafeNumber : {}",error.what());
    }
}


                                                

int main(){
    int numerical_precision;
    println(R"(  ______            _                _         _ 
 |  ____|          | |              (_)       | |
 | |__  __ _   ___ | |_  ___   _ __  _   __ _ | |
 |  __|/ _` | / __|| __|/ _ \ | '__|| | / _` || |
 | |  | (_| || (__ | |_| (_) || |   | || (_| || |
 |_|   \__,_| \___| \__|\___/ |_|   |_| \__,_||_|
                                                 
                                                 )");
    println("How many bits to use? (8,16,32,64)");
    cin >> numerical_precision;
    uint64_t number;
    println("Enter a number: ");
    cin >> number;
    switch (numerical_precision) {
        case 8:  print_results(static_cast<uint8_t>(number)); break;
        case 16: print_results(static_cast<uint16_t>(number)); break;
        case 32: print_results(static_cast<uint32_t>(number)); break;
        case 64: print_results(static_cast<uint64_t>(number)); break;
        default:
            println("Invalid number of bits");
    }
} 