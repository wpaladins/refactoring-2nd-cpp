#include "statement03.h"

#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

struct statement_data_t {
    const string& customer; // 使用 const &
    const performances_t& performances;
};

string renderPlainText(const statement_data_t& data, const plays_t& plays) {
    auto playFor = [&plays](const performance_t& aPerformance) -> const play_t& {
        return plays.at(aPerformance.playID);
    };

    auto amountFor = [&](const performance_t& aPerformance) {
        int result = 0;

        switch (playFor(aPerformance).type)
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

    auto volumeCreditsFor = [&](const performance_t& aPerformance) {
        int result = 0;
        result += max(aPerformance.audience - 30, 0);
        if (COMEDY_TYPE == playFor(aPerformance).type) {
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
            result += amountFor(perf);
        }
        return result;
    };

    ostringstream result;
    result << "Statement for " << data.customer << endl;

    for (auto& perf : data.performances) {
        result << "  " << playFor(perf).name + ": "
            << usd(amountFor(perf)) << " ("
            << to_string(perf.audience) << " seats)" << endl;
    }

    result << "Amount owed is " << usd(totalAmount()) << endl;
    result << "You earned " << to_string(totalVolumeCredits()) << " credits" << endl;
    return move(result).str();
}

// 拆分阶段(154)
// 提炼函数(106)
string statement03(const invoice_t& invoce, const plays_t& plays) {
    statement_data_t statementData{
        invoce.customer,
        invoce.performances
    };
    return renderPlainText(statementData, plays);
}
