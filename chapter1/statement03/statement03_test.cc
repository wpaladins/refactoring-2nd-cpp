#include "create_statement_data.h"
#include "statement03.h"

#include <gtest/gtest.h>
#include <vector>

using namespace std;

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

TEST(StatementTestSuite, CreateStatementDataTestCase03) {
    statement_data_t statementData = createStatementData(invoices[0], plays);

    ASSERT_EQ(statementData.customer, invoices[0].customer);
    EXPECT_EQ(statementData.totalAmount, 173000);
    EXPECT_EQ(statementData.totalVolumeCredits, 47);

    ASSERT_EQ(statementData.performances.size(), 3);
    vector<int> expectedAmounts{65000, 58000, 50000};
    vector<int> expectedAudience{55, 35, 40};
    for (int i = 0; i < 3; i++) {
        ASSERT_EQ(statementData.performances[i].playID, invoices[0].performances[i].playID);
        EXPECT_EQ(statementData.performances[i].amount, expectedAmounts[i]);
        EXPECT_EQ(statementData.performances[i].audience, expectedAudience[i]);
    }
}

TEST(StatementTestSuite, StatementTestCase03) {
    EXPECT_STREQ(statement03(invoices[0], plays).c_str(), "\
Statement for BigCo\n\
  Hamlet: $650.00 (55 seats)\n\
  As You Like It: $580.00 (35 seats)\n\
  Othello: $500.00 (40 seats)\n\
Amount owed is $1730.00\n\
You earned 47 credits\n"
    );
}

TEST(StatementTestSuite, HtmlStatementTestCase03) {
    EXPECT_STREQ(htmlStatement03(invoices[0], plays).c_str(), "\
<h1>Statement for BigCo</h1>\n\
<table>\n\
    <tr><th>play</th><th>seats</th><th>cost</th></tr>\n\
    <tr>\n\
        <td>Hamlet</td>\n\
        <td>55</td>\n\
        <td>$650.00</td>\n\
    </tr>\n\
    <tr>\n\
        <td>As You Like It</td>\n\
        <td>35</td>\n\
        <td>$580.00</td>\n\
    </tr>\n\
    <tr>\n\
        <td>Othello</td>\n\
        <td>40</td>\n\
        <td>$500.00</td>\n\
    </tr>\n\
</table>\n\
<p>Amount owed is <em>$1730.00</em></p>\n\
<p>You earned <em>47</em> credits</p>\n"
    );
}
