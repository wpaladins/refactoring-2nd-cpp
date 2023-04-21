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

class ProvinceTestSuite : public testing::Test {
protected:
    void SetUp() override {
        asia = make_unique<Province>(sampleProvinceData());
    }
    unique_ptr<Province> asia;
};

TEST_F(ProvinceTestSuite, shortfall) {
    ASSERT_EQ(asia->shortfall(), 5);
}

TEST_F(ProvinceTestSuite, profit) {
    EXPECT_EQ(asia->profit(), 230);
}

TEST_F(ProvinceTestSuite, changeProduction) {
    asia->producers()[0]->production(20);
    EXPECT_EQ(asia->shortfall(), -6);
    EXPECT_EQ(asia->profit(), 292);
}
