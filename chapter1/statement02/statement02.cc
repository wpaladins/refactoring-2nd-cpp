#include "statement02.h"

#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

string statement02(const invoice_t& invoce, const plays_t& plays) {
    // 以查询取代临时变量(178)
    auto playFor = [&plays](const performance_t& aPerformance) -> const play_t& { // 注意返回值类型
        return plays.at(aPerformance.playID); // 使用 at(), 因为 plays 是 const 的
    };

    // 提炼函数(106)
    // 该表函数声明(124)
    auto amountFor = [&](const performance_t& aPerformance) {
        float result = 0;

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
        // 内联变量(123)
        if (COMEDY_TYPE == playFor(aPerformance).type) {
            result += floor(aPerformance.audience / 5);
        }
        return result;
    };

    auto format = [](float aNumber) {
        return "$" + to_string(round(aNumber * 100)/100).substr(0, to_string(aNumber).find(".") + 3);
    };

    float total_amount = 0;
    int volume_credits = 0;

    ostringstream result;
    result << "Statement for " << invoce.customer << endl;

    for (auto& perf : invoce.performances) {
        volume_credits += volumeCreditsFor(perf);

        // 内联变量(123)
        result << "  " << playFor(perf).name + ": "
               << format(amountFor(perf) / 100) << " ("
               << to_string(perf.audience) << " seats)" << endl;
        total_amount += amountFor(perf);
    }
    result << "Amount owed is " << format(total_amount / 100) << endl;
    result << "You earned " << to_string(volume_credits) << " credits" << endl;
    return move(result).str();
}
