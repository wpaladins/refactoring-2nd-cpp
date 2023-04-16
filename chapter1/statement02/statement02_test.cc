#include "statement02.h"

#include <gtest/gtest.h>

// 剧目
plays_t plays
{
    {
        "hamlet",
        {
            "Hamlet", TRAGEDY_TYPE
        }
    },
        {
        "as-like",
        {
            "As You Like It", COMEDY_TYPE
        }
    },
        {
        "othello",
        {
            "Othello", TRAGEDY_TYPE
        }
    }
};

// 账单
invoices_t invoices
{
    {
        "BigCo",
        {
            {
                "hamlet",
                55
            },
            {
                "as-like",
                35
            },
            {
                "othello",
                40
            }
        }
    }
};

TEST(StatementTestSuite, StatementTestCase02) {
    EXPECT_STREQ(statement02(invoices[0], plays).c_str(), "\
Statement for BigCo\n\
  Hamlet: $650.00 (55 seats)\n\
  As You Like It: $580.00 (35 seats)\n\
  Othello: $500.00 (40 seats)\n\
Amount owed is $1730.00\n\
You earned 47 credits\n"
    );
}
