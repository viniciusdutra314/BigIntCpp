#include <cstdint>
#include <vector>
#include <gtest/gtest.h>
#include "big_int.hpp"

TEST(BigInt,Comparisions){
    //Igualdade
    EXPECT_EQ(123_bigint,123_bigint);
    EXPECT_NE(123_bigint,-123_bigint);
    EXPECT_NE(123456789_bigint,123456780_bigint);
    auto x=123_bigint;
    EXPECT_TRUE(x.get_digits()==std::vector<uint32_t>{123});
    x=12323456789_bigint;
    std::vector<uint32_t> digits{23456789,123};
    EXPECT_TRUE(x.get_digits()==digits);

    //Comparações;

    EXPECT_EQ(-(-200_bigint),200_bigint);
    EXPECT_TRUE(200_bigint>100_bigint);
    EXPECT_TRUE(200_bigint>=100_bigint);
    EXPECT_TRUE(-200_bigint<100_bigint);
    EXPECT_TRUE(-200_bigint<=100_bigint);
    EXPECT_TRUE(100000000000000000000000000_bigint>=100_bigint);
    EXPECT_TRUE(100_bigint<=100000000000000000000000000_bigint);
    EXPECT_TRUE(100_bigint>=-100000000000000000000000000_bigint);
    EXPECT_TRUE(1385138138513813851381385138138513813851381385138_bigint>
        1385138138513813851381345138138513813851381385138_bigint);
}
