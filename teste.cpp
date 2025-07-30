#include "big_int.hpp"
#include <print>

int main(){
    BigInteger number=+537895687913659831659836190583176501365713651305315613071671035606131165361_bigint;
    BigInteger other_number=-number;
    if (number==other_number){
        println("Números são iguais");
    };
    auto& digits=number.get_digits();
    for (auto& digit: views::reverse(digits)){
        println("{}",digit);
    }
}