#include "statement03.h"

#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

// 复制 performance_t 中的信息, 而其他信息仅引用
struct enriched_performance_t : public performance_t {
    const play_t& play;
    int amount;
    enriched_performance_t(const performance_t& parent,
                           const play_t& play)
                           : performance_t(parent),
                             play(play) {}
};

using enriched_performances_t = vector<enriched_performance_t>;

struct statement_data_t {
    const string& customer; // 使用 const &
    const enriched_performances_t& performances;
};

// 保持数据不可变(不修改传给函数的参数)
string renderPlainText(const statement_data_t& data, const plays_t& plays) {
    auto volumeCreditsFor = [&](const enriched_performance_t& aPerformance) {
        int result = 0;
        result += max(aPerformance.audience - 30, 0);
        if (COMEDY_TYPE == aPerformance.play.type) {
            result += floor(aPerformance.audience / 5);
        }
        return result;
    };

    auto usd = [](int aNumber) {
        string number_str = to_string(float(aNumber)/100);
        return "$" + number_str.substr(0, number_str.find(".") + 3);
    };

    auto totalVolumeCredits = [&]() {
        int result = 0;
        for (auto& perf : data.performances) {
            result += volumeCreditsFor(perf);
        }
        return result;
    };

    auto totalAmount = [&]() {
        int result = 0;
        for (auto& perf : data.performances) {
            result += perf.amount;
        }
        return result;
    };

    ostringstream result;
    result << "Statement for " << data.customer << endl;

    for (auto& perf : data.performances) {
        result << "  " << perf.play.name + ": "
            << usd(perf.amount) << " ("
            << to_string(perf.audience) << " seats)" << endl;
    }

    result << "Amount owed is " << usd(totalAmount()) << endl;
    result << "You earned " << to_string(totalVolumeCredits()) << " credits" << endl;
    return move(result).str();
}

// 拆分阶段(154)
// 提炼函数(106)
string statement03(const invoice_t& invoce, const plays_t& plays) {
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

    enriched_performances_t enriched_performances;
    for_each(invoce.performances.begin(), invoce.performances.end(), [&](auto& aPerformance) {
        enriched_performances.emplace_back(aPerformance, playFor(aPerformance));
        enriched_performances.back().amount = amountFor(enriched_performances.back());
    });

    statement_data_t statementData{
        invoce.customer,
        enriched_performances
    };

    return renderPlainText(statementData, plays);
}
