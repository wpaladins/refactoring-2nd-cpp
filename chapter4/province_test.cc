#include "province.h"

#include <gtest/gtest.h>

using namespace std;

ProvinceData sampleProvinceData() {
    return {
        "Asia",
        {
            {"Byzantium", 10, 9},
            {"Attalia", 12, 10},
            {"Sinope", 10, 6}
        },
        30,
        20
    };
}

TEST(province, shortfall) {
    auto asia = make_unique<Province>(sampleProvinceData());
    ASSERT_EQ(asia->shortfall(), 5);
}

TEST(province, profit) {
    auto asia = make_unique<Province>(sampleProvinceData());
    EXPECT_EQ(asia->profit(), 230);
}
