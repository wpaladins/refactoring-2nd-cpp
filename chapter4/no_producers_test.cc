#include "province.h"

#include <gtest/gtest.h>

using namespace std;

class NoProducersTestSuite : public testing::Test {
protected:
    void SetUp() override {
        ProvinceData data{
            "No producers",
            {},
            30,
            20
        };
        noProducers = make_unique<Province>(data);
    }
    unique_ptr<Province> noProducers;
};

TEST_F(NoProducersTestSuite, shortfall) {
    ASSERT_EQ(noProducers->shortfall(), 30);
}

TEST_F(NoProducersTestSuite, profit) {
    EXPECT_EQ(noProducers->profit(), 0);
}
