#include "safe_number.hpp"
#include <cstdint>
#include <print>

template<typename Number>
Number factorial(Number n){
    Number result=n;
    while (n!=0){
        n=n-1;
        result=result*n;
    }
    return result;
}


int main(){
    factorial(SafeNumber(uint8_t(2)));

}