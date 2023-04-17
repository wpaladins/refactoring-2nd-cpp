#include "statement03.h"

#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <sstream>

using namespace std;

// 保持数据不可变(不修改传给函数的参数)
string renderPlainText(const statement_data_t& data, const plays_t& plays) {
    auto usd = [](int aNumber) {
        string number_str = to_string(float(aNumber)/100);
        return "$" + number_str.substr(0, number_str.find(".") + 3);
    };

    ostringstream result;
    result << "Statement for " << data.customer << endl;

    for (auto& perf : data.performances) {
        result << "  " << perf.play.name + ": "
            << usd(perf.amount) << " ("
            << to_string(perf.audience) << " seats)" << endl;
    }

    result << "Amount owed is " << usd(data.totalAmount) << endl;
    result << "You earned " << to_string(data.totalVolumeCredits) << " credits" << endl;
    return move(result).str();
}

// 拆分阶段(154)
// 提炼函数(106)
statement_data_t createStatementData(const invoice_t& invoce, const plays_t& plays) {
    // 搬移函数(198)
    auto playFor = [&plays](const performance_t& aPerformance) -> const play_t& {
        return plays.at(aPerformance.playID);
    };

    auto amountFor = [&](const enriched_performance_t& aPerformance) {
        int result = 0;

        switch (aPerformance.play.type)
        {
        case TRAGEDY_TYPE:
            result = 40000;
            if (aPerformance.audience > 30) {
                result += 1000 * (aPerformance.audience - 30);
            }
            break;

        case COMEDY_TYPE:
            result = 30000;
            if (aPerformance.audience > 20) {
                result += 10000 + 500 * (aPerformance.audience - 20);
            }
            result += 300 * aPerformance.audience;
            break;

        default:
            exit(-1);
        }
        return result;
    };

    auto volumeCreditsFor = [&](const enriched_performance_t& aPerformance) {
        int result = 0;
        result += max(aPerformance.audience - 30, 0);
        if (COMEDY_TYPE == aPerformance.play.type) {
            result += floor(aPerformance.audience / 5);
        }
        return result;
    };

    // 以管道取代循环(231)
    auto totalVolumeCredits = [&](const statement_data_t& data) {
        return accumulate(data.performances.begin(), data.performances.end(), 0, [](int result, const enriched_performance_t& aPerformance) {
            return result + aPerformance.volumeCredits;
        });
    };

    // 以管道取代循环(231)
    auto totalAmount = [&](const statement_data_t& data) {
        return accumulate(data.performances.begin(), data.performances.end(), 0, [](int result, const enriched_performance_t& aPerformance) {
            return result + aPerformance.amount;
        });
    };

    enriched_performances_t enriched_performances;
    for_each(invoce.performances.begin(), invoce.performances.end(), [&](auto& aPerformance) {
        enriched_performances.emplace_back(aPerformance, playFor(aPerformance));
        enriched_performances.back().amount = amountFor(enriched_performances.back());
        enriched_performances.back().volumeCredits = volumeCreditsFor(enriched_performances.back());
    });

    statement_data_t statementData{
        invoce.customer,
        move(enriched_performances) // pay attention
    };
    statementData.totalAmount = totalAmount(statementData);
    statementData.totalVolumeCredits = totalVolumeCredits(statementData);

    return statementData;
}

string statement03(const invoice_t& invoice, const plays_t& plays) {
    return renderPlainText(createStatementData(invoice, plays), plays);
}
